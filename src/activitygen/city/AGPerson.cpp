/****************************************************************************/
/// @file    AGPerson.cpp
/// @author  Piotr Woznica
/// @author  Walter Bamberger
/// @author  Daniel Krajzewicz
/// @date    July 2010
/// @version $Id$
///
// Parent object of every person, contains age and any natural characteristic
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.sourceforge.net/
// Copyright (C) 2001-2013 DLR (http://www.dlr.de/) and contributors
// activitygen module
// Copyright 2010 TUM (Technische Universitaet Muenchen, http://www.tum.de/)
/****************************************************************************/
//
//   This file is part of SUMO.
//   SUMO is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include "AGPerson.h"
#include <utils/common/RandHelper.h>
#include <iostream>


// ===========================================================================
// used namespaces
// ===========================================================================
using namespace std;


// ===========================================================================
// method definitions
// ===========================================================================
AGPerson::AGPerson(int age) : age(age) {}

/****************************************************************************/

AGPerson::~AGPerson() {}

/****************************************************************************/

void
AGPerson::print() const {
    cout << "- Person: Age=" << age << endl;
}

/****************************************************************************/

int
AGPerson::getAge() const {
    return age;
}

/****************************************************************************/

bool
AGPerson::decide(SUMOReal proba) const {
    return (RandHelper::rand(1000) < static_cast<int>(1000.0f * proba));
}

/****************************************************************************/
