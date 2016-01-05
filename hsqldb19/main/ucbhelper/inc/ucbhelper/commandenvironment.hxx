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



#ifndef _UCBHELPER_COMMANDENVIRONMENT_HXX
#define _UCBHELPER_COMMANDENVIRONMENT_HXX

#include <com/sun/star/lang/XTypeProvider.hpp>
#ifndef _COM_SUN_STAR_UCB_XCOMMMANDENVIRONMENT_HPP_
#include <com/sun/star/ucb/XCommandEnvironment.hpp>
#endif
#include <cppuhelper/weak.hxx>
#include <ucbhelper/macros.hxx>
#include "ucbhelper/ucbhelperdllapi.h"

namespace ucbhelper
{

struct CommandEnvironment_Impl;

//=========================================================================

/**
  * This class implements the interface
  * com::sun::star::ucb::XCommandEnvironement. Instances of this class can
  * be used to supply environments to commands executed by UCB contents.
  */
class UCBHELPER_DLLPUBLIC CommandEnvironment : public cppu::OWeakObject,
						   public com::sun::star::lang::XTypeProvider,
						   public com::sun::star::ucb::XCommandEnvironment
{
	CommandEnvironment_Impl* m_pImpl;

private:
	UCBHELPER_DLLPRIVATE CommandEnvironment( const CommandEnvironment& ); 				// n.i.
    UCBHELPER_DLLPRIVATE CommandEnvironment& operator=( const CommandEnvironment& ); 	// n.i.

public:
	/**
	  * Constructor.
	  *
	  * @param rxInteractionHandler is the implementation of an Interaction
	  *        Handler or an empty reference.
	  * @param rxProgressHandler is the implementation of a Progress
	  *        Handler or an empty reference.
	  */
	CommandEnvironment(
			const com::sun::star::uno::Reference<
				com::sun::star::task::XInteractionHandler >&
					rxInteractionHandler,
			const com::sun::star::uno::Reference<
				com::sun::star::ucb::XProgressHandler >&
					rxProgressHandler );
	/**
	  * Destructor.
	  */
	virtual ~CommandEnvironment();

	// XInterface
	XINTERFACE_DECL()

	// XTypeProvider
	XTYPEPROVIDER_DECL()

 	// XCommandEnvironemnt
	virtual com::sun::star::uno::Reference<
				com::sun::star::task::XInteractionHandler > SAL_CALL
	getInteractionHandler()
		throw ( com::sun::star::uno::RuntimeException );

	virtual com::sun::star::uno::Reference<
				com::sun::star::ucb::XProgressHandler > SAL_CALL
	getProgressHandler()
		throw ( com::sun::star::uno::RuntimeException );
};

} /* namespace ucbhelper */

#endif /* !_UCBHELPER_COMMANDENVIRONMENT_HXX */
