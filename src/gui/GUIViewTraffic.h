/****************************************************************************/
/// @file    GUIViewTraffic.h
/// @author  Daniel Krajzewicz
/// @date    Sept 2002
/// @version $Id: $
///
// A view on the simulation; this view is a microscopic one
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.sourceforge.net/
// copyright : (C) 2001-2007
//  by DLR (http://www.dlr.de/) and ZAIK (http://www.zaik.uni-koeln.de/AFS)
/****************************************************************************/
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef GUIViewTraffic_h
#define GUIViewTraffic_h
// ===========================================================================
// compiler pragmas
// ===========================================================================
#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif


// ===========================================================================
// included modules
// ===========================================================================
#ifdef WIN32
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <string>
#include <utils/geom/Boundary.h>
#include <utils/geom/Position2D.h>
#include <utils/gfx/RGBColor.h>
#include <utils/geom/Position2DVector.h>
#include <utils/shapes/Polygon2D.h>
#include "GUISUMOViewParent.h"
#include <utils/gui/windows/GUISUMOAbstractView.h>
#include <utils/gui/drawer/GUIColoringSchemesMap.h>
#include <utils/gui/drawer/GUILaneDrawer.h>
#include "drawerimpl/GUIVehicleDrawer.h"
#include "drawerimpl/GUIDetectorDrawer.h"
#include "drawerimpl/GUIROWDrawer.h"
#include "drawerimpl/GUIJunctionDrawer.h"
#include <utils/gui/globjects/GUIGlObject_AbstractAdd.h>

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>


// ===========================================================================
// class declarations
// ===========================================================================
class MSVehicle;
class GUINet;
class GUISUMOViewParent;
class GUIVehicle;
class GUILaneWrapper;
class GUIEdge;
class GUIPerspectiveChanger;


// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class GUIViewTraffic
 * Microsocopic view at the simulation
 */
class GUIViewTraffic : public GUISUMOAbstractView
{
    FXDECLARE(GUIViewTraffic)
public:
    /// constructor
    GUIViewTraffic(FXComposite *p, GUIMainWindow &app,
                   GUISUMOViewParent *parent, GUINet &net, FXGLVisual *glVis);

    /// constructor
    GUIViewTraffic(FXComposite *p, GUIMainWindow &app,
                   GUISUMOViewParent *parent, GUINet &net, FXGLVisual *glVis,
                   FXGLCanvas *share);
    void init(GUINet &net) ;

    void create();

    /// destructor
    virtual ~GUIViewTraffic();

    /// builds the view toolbars
    virtual void buildViewToolBars(GUIGlChildWindow &);

    void startTrack(int id);
    void stopTrack();
    int getTrackedID() const;

    long onCmdChangeColorScheme(FXObject*,FXSelector sel,void*);
    long onLeftBtnPress(FXObject *o,FXSelector sel,void *data);
    long onLeftBtnRelease(FXObject*,FXSelector,void*);
    long onMouseMove(FXObject *o,FXSelector sel,void *data);


    void centerTo(GUIGlObject *o);
    void rename(GUIGlObject *o);
    void moveTo(GUIGlObject *o);
    void changeCol(GUIGlObject *o);
    void changeTyp(GUIGlObject *o);
    void deleteObj(GUIGlObject *o);

    /// shows a vehicle route
    void showRoute(GUIVehicle *v, int index=-1);

    /// hides a vehicle route
    void hideRoute(GUIVehicle *v, int index=-1);

    /// Returns the information whether the route of the given vehicle is shown
    bool amShowingRouteFor(GUIVehicle *v, int index=-1);

    virtual long onCmdEditView(FXObject*,FXSelector,void*);

    /// Returns the list of available vehicle coloring schemes
    static GUIColoringSchemesMap<GUIVehicle> &getVehiclesSchemesMap();

    /// Returns the list of available lane coloring schemes
    static GUIColoringSchemesMap<GUILaneWrapper> &getLaneSchemesMap();


protected:
    void doPaintGL(int mode, SUMOReal scale);

    void doInit();

    /// returns the color of the edge
    RGBColor getEdgeColor(GUIEdge *edge) const;

    void drawRoute(const VehicleOps &vo, int routeNo, SUMOReal darken);

    void setPointToMove(PointOfInterest *p);
    void setIdToMove(unsigned int id);
    void draw(const MSRoute &r);
    void setFirstPoint(PointOfInterest *p);
    void setSecondPoint(PointOfInterest *p);

protected:
    /** @brief Instances of the vehicle drawers
        A drawer is chosen in dependence to whether the full or the simple
        geometry shall be used and whether to show tooltips or not */
    GUIVehicleDrawer myVehicleDrawer;

    /** @brief Instances of the lane drawers
        A drawer is chosen in dependence to whether the full or the simple
        geometry shall be used and whether to show tooltips or not */
    GUILaneDrawer<GUIEdge, GUIEdge, GUILaneWrapper> myLaneDrawer;

    /** @brief Instances of the junction drawers
        A drawer is chosen in dependence to whether the full or the simple
        geometry shall be used and whether to show tooltips or not */
    GUIJunctionDrawer myJunctionDrawer;

    /** @brief Instances of the detectors drawers
        A drawer is chosen in dependence to whether the full or the simple
        geometry shall be used and whether to show tooltips or not */
    GUIDetectorDrawer myDetectorDrawer;

    /** @brief Instances of the right of way drawers
        A drawer is chosen in dependence to whether the full or the simple
        geometry shall be used and whether to show tooltips or not */
    GUIROWDrawer myROWDrawer;

    /// The coloring scheme of junctions to use
    JunctionColoringScheme _junctionColScheme;

    int myTrackedID;

    /** @brief Pointers to tables holding the information which of the items are visible
        All vehicles on visible edges will be drawn */
    size_t *_edges2Show, *_junctions2Show, *_additional2Show;

    /// The absolut numbers of the array sizes
    size_t _edges2ShowSize, _junctions2ShowSize, _additional2ShowSize;

    PointOfInterest *_pointToMove;
    PointOfInterest *_secondPoint; // first's Line Point
    PointOfInterest *_firstPoint;  // second's Line Point
    unsigned int _IdToMove;  // for deleting the _pointToMove also into gIDStorage
    bool _leftButtonPressed; // set to true if the left Button is pressed and keep pressed

    GUINet *_net;

    /** @brief The list of vehicle coloring schemes that may be used */
    static GUIColoringSchemesMap<GUIVehicle> myVehicleColoringSchemes;

    /** @brief The list of coloring schemes that may be used */
    static GUIColoringSchemesMap<GUILaneWrapper> myLaneColoringSchemes;


protected:
    std::vector<GUIEdge*> myEmptyEdges;
    std::vector<GUIJunctionWrapper*> myEmptyJunctions;

    GUIViewTraffic()
            : myVehicleDrawer(myEmptyEdges), myLaneDrawer(myEmptyEdges),
            myJunctionDrawer(myEmptyJunctions),
            myDetectorDrawer(GUIGlObject_AbstractAdd::getObjectList()),
            myROWDrawer(myEmptyEdges)
    { }

};


#endif

/****************************************************************************/

