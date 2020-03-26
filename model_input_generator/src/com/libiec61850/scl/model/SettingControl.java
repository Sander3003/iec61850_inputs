package com.libiec61850.scl.model;

import org.w3c.dom.Node;

import com.libiec61850.scl.ParserUtils;
import com.libiec61850.scl.SclParserException;

/*
 *  Copyright 2014 Michael Zillgith
 *
 *  This file is part of libIEC61850.
 *
 *  libIEC61850 is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  libIEC61850 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libIEC61850.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  See COPYING file for the complete license text.
 */

public class SettingControl {
	
	private String desc;
	private int numOfSGs = 1;
	private int actSG = 1;

	public SettingControl(Node settingControlNode) throws SclParserException {
		desc = ParserUtils.parseAttribute(settingControlNode, "desc");
		
		String numOfSGsString = ParserUtils.parseAttribute(settingControlNode, "numOfSGs");
		
		if (numOfSGsString != null)
			numOfSGs = Integer.decode(numOfSGsString);
		
		String actSGString = ParserUtils.parseAttribute(settingControlNode, "actSG");
		
		if (actSGString != null)
			actSG = Integer.decode(actSGString);
	}

	public String getDesc() {
		return desc;
	}

	public int getNumOfSGs() {
		return numOfSGs;
	}

	public int getActSG() {
		return actSG;
	}
	
}
