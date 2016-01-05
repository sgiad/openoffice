/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_sfx2.hxx"

#include "plugin.hxx"
#include <com/sun/star/plugin/XPluginManager.hpp>
#include <com/sun/star/plugin/PluginMode.hpp>
#include <com/sun/star/awt/XControl.hpp>

#include <tools/debug.hxx>
#include <rtl/ustring.hxx>
#include <toolkit/helper/vclunohelper.hxx>
#include <svtools/miscopt.hxx>
#include <vcl/window.hxx>

using namespace ::com::sun::star;

namespace sfx2
{

class PluginWindow_Impl : public Window
{
public:
    uno::Reference < awt::XWindow > xWindow;
    PluginWindow_Impl( Window* pParent )
     : Window( pParent, WB_CLIPCHILDREN )
     {}

     virtual void Resize();
};

void PluginWindow_Impl::Resize()
{
    Size aSize( GetOutputSizePixel() );
    if ( xWindow.is() )
        xWindow->setPosSize( 0, 0, aSize.Width(), aSize.Height(), WINDOW_POSSIZE_SIZE );
}

#define PROPERTY_UNBOUND 0

#define WID_COMMANDS    1
#define WID_MIMETYPE    2
#define WID_URL         3
const SfxItemPropertyMapEntry* lcl_GetPluginPropertyMap_Impl()
{
    static SfxItemPropertyMapEntry aPluginPropertyMap_Impl[] =
    {
        { MAP_CHAR_LEN("PluginCommands"), WID_COMMANDS, &::getCppuType((::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >*)0), PROPERTY_UNBOUND, 0},
        { MAP_CHAR_LEN("PluginMimeType"), WID_MIMETYPE, &::getCppuType((const ::rtl::OUString*)0), PROPERTY_UNBOUND, 0 },
        { MAP_CHAR_LEN("PluginURL"),      WID_URL     , &::getCppuType((const ::rtl::OUString*)0), PROPERTY_UNBOUND, 0 },
        {0,0,0,0,0,0}
    };
    return aPluginPropertyMap_Impl;
}

SFX_IMPL_XSERVICEINFO( PluginObject, "com.sun.star.embed.SpecialEmbeddedObject", "com.sun.star.comp.sfx2.PluginObject" )
SFX_IMPL_SINGLEFACTORY( PluginObject );

PluginObject::PluginObject( const uno::Reference < lang::XMultiServiceFactory >& rFact )
    : mxFact( rFact )
    , maPropMap( lcl_GetPluginPropertyMap_Impl() )
{
}

PluginObject::~PluginObject()
{
}

void SAL_CALL PluginObject::initialize( const uno::Sequence< uno::Any >& aArguments ) throw ( uno::Exception, uno::RuntimeException )
{
	if ( aArguments.getLength() )
        aArguments[0] >>= mxObj;
}

sal_Bool SAL_CALL PluginObject::load( 
    const uno::Sequence < com::sun::star::beans::PropertyValue >& /*lDescriptor*/,
    const uno::Reference < frame::XFrame >& xFrame ) 
throw( uno::RuntimeException )
{
    uno::Reference< plugin::XPluginManager > xPMgr( mxFact->createInstance( ::rtl::OUString::createFromAscii("com.sun.star.plugin.PluginManager") ), uno::UNO_QUERY );
    if (!xPMgr.is() )
        return sal_False;

    if ( SvtMiscOptions().IsPluginsEnabled() )
    {
        Window* pParent = VCLUnoHelper::GetWindow( xFrame->getContainerWindow() );
        PluginWindow_Impl* pWin = new PluginWindow_Impl( pParent );
        pWin->SetSizePixel( pParent->GetOutputSizePixel() );
        pWin->SetBackground();
        pWin->Show();

        sal_uIntPtr nCount = maCmdList.Count();
        uno::Sequence < ::rtl::OUString > aCmds( nCount ), aArgs( nCount );
        ::rtl::OUString *pCmds = aCmds.getArray(), *pArgs = aArgs.getArray();
        for( sal_uIntPtr i = 0; i < nCount; i++ )
        {
            SvCommand & rCmd = maCmdList.GetObject( i );
            pCmds[i] = rCmd.GetCommand();
            pArgs[i] = rCmd.GetArgument();
        }

        mxPlugin = xPMgr->createPluginFromURL(
            xPMgr->createPluginContext(), plugin::PluginMode::EMBED, aCmds, aArgs, uno::Reference< awt::XToolkit >(),
            uno::Reference< awt::XWindowPeer >( pWin->GetComponentInterface() ), maURL );

        if ( mxPlugin.is() )
        {
            uno::Reference< awt::XWindow > xWindow( mxPlugin, uno::UNO_QUERY );
            if ( xWindow.is() )
            {
                pWin->xWindow = xWindow;
                pWin->Resize();
                xWindow->setVisible( sal_True );
            }

            try
            {
                uno::Reference< awt::XControl > xControl( mxPlugin, uno::UNO_QUERY );
                if( xControl.is() )
                {
                    uno::Reference< awt::XControlModel > xModel = xControl->getModel();
                    uno::Reference< beans::XPropertySet > xProp( xModel, ::uno::UNO_QUERY );
                    if( xProp.is() )
                    {
                        uno::Any aValue = xProp->getPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "URL" ) ) );
                        aValue >>= maURL;
                        aValue = xProp->getPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "TYPE" ) ) );
                        aValue >>= maMimeType;
                    }
                }
            }
            catch( uno::Exception& )
            {
            }
        }

        uno::Reference < awt::XWindow > xWindow( pWin->GetComponentInterface(), uno::UNO_QUERY );

        // we must destroy the plugin before the parent is destroyed
        xWindow->addEventListener( this );
        xFrame->setComponent( xWindow, uno::Reference < frame::XController >() );
        return mxPlugin.is() ? sal_True : sal_False;
    }

    return sal_False;
}

void SAL_CALL PluginObject::cancel() throw( com::sun::star::uno::RuntimeException )
{
    uno::Reference< lang::XComponent > xComp( mxPlugin, uno::UNO_QUERY );
	if (xComp.is())
		xComp->dispose();
    mxPlugin = 0;
}

void SAL_CALL PluginObject::close( sal_Bool /*bDeliverOwnership*/ ) throw( com::sun::star::util::CloseVetoException, com::sun::star::uno::RuntimeException )
{
}

void SAL_CALL PluginObject::addCloseListener( const com::sun::star::uno::Reference < com::sun::star::util::XCloseListener >& ) throw( com::sun::star::uno::RuntimeException )
{
}

void SAL_CALL PluginObject::removeCloseListener( const com::sun::star::uno::Reference < com::sun::star::util::XCloseListener >& ) throw( com::sun::star::uno::RuntimeException )
{
}

void SAL_CALL PluginObject::disposing( const com::sun::star::lang::EventObject& ) throw (com::sun::star::uno::RuntimeException)
{
    cancel();
}

uno::Reference< beans::XPropertySetInfo > SAL_CALL PluginObject::getPropertySetInfo() throw( ::com::sun::star::uno::RuntimeException )
{
    static uno::Reference< beans::XPropertySetInfo > xInfo = new SfxItemPropertySetInfo( &maPropMap );
    return xInfo;
}

void SAL_CALL PluginObject::setPropertyValue(const ::rtl::OUString& aPropertyName, const uno::Any& aAny)
    throw ( beans::UnknownPropertyException, beans::PropertyVetoException, lang::IllegalArgumentException, lang::WrappedTargetException, uno::RuntimeException)
{
    if ( aPropertyName.equalsAscii("PluginURL") )
    {
        aAny >>= maURL;
    }
    else if ( aPropertyName.equalsAscii("PluginMimeType") )
    {
        aAny >>= maMimeType;
    }
    else if ( aPropertyName.equalsAscii("PluginCommands") )
    {
        maCmdList.Clear();
        uno::Sequence < beans::PropertyValue > aCommandSequence;
        if( aAny >>= aCommandSequence )
            maCmdList.FillFromSequence( aCommandSequence );
    }
    else
         throw beans::UnknownPropertyException();
}

uno::Any SAL_CALL PluginObject::getPropertyValue(const ::rtl::OUString& aPropertyName)
        throw ( beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
    uno::Any aAny;
    if ( aPropertyName.equalsAscii("PluginURL") )
    {
        aAny <<= maURL;
    }
    else if ( aPropertyName.equalsAscii("PluginMimeType") )
    {
        aAny <<= maMimeType;
    }
    else if ( aPropertyName.equalsAscii("PluginCommands") )
    {
        uno::Sequence< beans::PropertyValue > aCommandSequence;
        maCmdList.FillSequence( aCommandSequence );
        aAny <<= aCommandSequence;
    }
    else
         throw beans::UnknownPropertyException();
    return aAny;
}

void SAL_CALL PluginObject::addPropertyChangeListener(const ::rtl::OUString&, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertyChangeListener > & ) throw( ::com::sun::star::uno::RuntimeException )
{
}

void SAL_CALL PluginObject::removePropertyChangeListener(const ::rtl::OUString&, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertyChangeListener > & ) throw( ::com::sun::star::uno::RuntimeException )
{
}

void SAL_CALL PluginObject::addVetoableChangeListener(const ::rtl::OUString&, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XVetoableChangeListener > & ) throw( ::com::sun::star::uno::RuntimeException )
{
}

void SAL_CALL PluginObject::removeVetoableChangeListener(const ::rtl::OUString&, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XVetoableChangeListener > & ) throw( ::com::sun::star::uno::RuntimeException )
{
}

}
