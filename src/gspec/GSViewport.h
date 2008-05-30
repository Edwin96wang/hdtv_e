/*
 * gSpec - a viewer for gamma spectra
 *  Copyright (C) 2006  Norbert Braun <n.braun@ikp.uni-koeln.de>
 *
 * This file is part of gSpec.
 *
 * gSpec is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * gSpec is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gSpec; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 * 
 */

#ifndef __GSViewport_h__
#define __GSViewport_h__

#include <vector>
#include <TGFrame.h>
#include <TGScrollBar.h>
#include <TGStatusBar.h>
#include "GSPainter.h"
#include "GSDisplaySpec.h"
#include "GSXMarker.h"
#include "GSYMarker.h"

class GSViewport : public TGFrame { 
 public:
  GSViewport(const TGWindow *p, UInt_t w, UInt_t h);
  ~GSViewport(void);
  void SetXOffset(double offset, bool update=true);
  void SetYOffset(double offset, bool update=true);
  void ShiftXOffset(double f, bool update=true);
  void ShiftYOffset(double f, bool update=true);
  inline double GetOffset(void) { return fXOffset; }
  void Update(bool redraw=false);
  void HandleScrollbar(Long_t parm);
  void SetXVisibleRegion(double region, bool update=true);
  void SetYVisibleRegion(double region, bool update=true);
  void XZoomAroundCursor(double f);
  void YZoomAroundCursor(double f);
  void ToBegin(void);
  void ShowAll(void);
  void SetViewMode(EViewMode vm);
  inline EViewMode GetViewMode(void) { return fPainter->GetViewMode(); }
  void SetLogScale(Bool_t l);
  inline void ToggleLogScale(void) { SetLogScale(!GetLogScale()); }
  inline Bool_t GetLogScale(void) { return fPainter->GetLogScale(); }
  void SetYAutoScale(bool as, bool update=true);
  inline Bool_t GetYAutoScale(void) { return fYAutoScale; }
  void YAutoScaleOnce(bool update=true);
  void Layout(void);
  void UpdateScrollbarRange(void);
  inline void SetScrollbar(TGHScrollBar *sb) { fScrollbar = sb; }
  void SetStatusBar(TGStatusBar *sb);
  double GetCursorX();
  double GetCursorY();
  int FindMarkerNearestCursor(int tol=3);
  
  /*** Object management functions ***/
  int AddXMarker(double pos, int color=defaultColor, bool update=true);
  GSXMarker *GetXMarker(int id);
  int FindNearestXMarker(double e, double tol=-1.0);
  void DeleteXMarker(int id, bool update=true);
  void DeleteAllXMarkers(bool update=true);

  int AddYMarker(double pos, int color=defaultColor, bool update=true);
  GSYMarker *GetYMarker(int id);
  void DeleteYMarker(int id, bool update=true);
  void DeleteAllYMarkers(bool update=true);

  int AddSpec(const TH1D *spec, int color=defaultColor, bool update=true);
  GSDisplaySpec *GetDisplaySpec(int id);
  //void SetSpecCal(int id, double cal0, double cal1, double cal2, double cal3, bool update);
  void DeleteSpec(int id, bool update=true);
  void DeleteAllSpecs(bool update=true);

  int AddFunc(const TF1 *func, int color=defaultColor, bool update=true);
  GSDisplayFunc *GetDisplayFunc(int id);
  //void SetFuncCal(int id, double cal0, double cal1, double cal2, double cal3, bool update);
  void DeleteFunc(int id, bool update=true);
  void DeleteAllFuncs(bool update=true);
   
  ClassDef(GSViewport, 1)
  
 protected:
  void DoRedraw(void);
  void DrawRegion(UInt_t x1, UInt_t x2);
  Bool_t HandleMotion(Event_t *ev);
  Bool_t HandleButton(Event_t *ev);
  Bool_t HandleCrossing(Event_t *ev);
  void DrawCursor(void);
  void ShiftOffset(int dO);
  template <class itemType>
  int FindFreeId(std::vector<itemType> &items);
  template <class itemType>
  void DeleteItem(std::vector<itemType> &items, int id);
  
  void UpdateStatusPos();
  void UpdateStatusScale();
 
 protected:
  double fXVisibleRegion, fYVisibleRegion;
  double fYMinVisibleRegion;
  double fXOffset, fYOffset;
  double fMinEnergy, fMaxEnergy;
  std::vector<GSDisplaySpec *> fSpectra;
  std::vector<GSDisplayFunc *> fFunctions;
  std::vector<GSXMarker *> fXMarkers;
  std::vector<GSYMarker *> fYMarkers;
  Bool_t fYAutoScale;
  Bool_t fNeedClear;
  TGGC *fCursorGC;
  UInt_t fCursorX, fCursorY;
  Bool_t fCursorVisible;
  Bool_t fDragging;
  UInt_t fLeftBorder, fRightBorder, fTopBorder, fBottomBorder;
  GSPainter *fPainter;
  TGHScrollBar *fScrollbar;
  TGStatusBar *fStatusBar;

  //  ClassDef(ViewerFrame,0)
};

#endif
