/**
 *****************************************************************************
 Copyright (c) 2015-16 IBM Corporation and other Contributors.
 All rights reserved. This program and the accompanying materials
 are made available under the terms of the Eclipse Public License v1.0
 which accompanies this distribution, and is available at
 http://www.eclipse.org/legal/epl-v10.html
 Contributors:
 Sathiskumar Palaniappan - Initial Contribution
 *****************************************************************************
 *
 */
package com.ibm.iotf.client.app;


public interface CommandCallback {

	/**
	 * 
	 * process the command received
	 * 
	 * @param cmd
	 *               Application subscribes to this command on the behalf of a device
	 */	

	public void processCommand(Command cmd);
}
