#include <QuickDraw.h>
#include <Windows.h>
#include <Events.h>
#include <stdio.h>
#include <stdlib.h>
#include "input.h"

#define GRID_SIZE 8
#define CELL_SIZE 20
#define LEFT_MARGIN 20
#define TOP_MARGIN 20

static GrafPort sysPort;
static double userGrid[GRID_SIZE * GRID_SIZE];

/* Manually define black & white patterns */
static Pattern blackPattern = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static Pattern whitePattern = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static WindowPtr CreateMainWindow(void);
static void DrawGrid(WindowPtr win);
static void HandleMouseDown(EventRecord *theEvent, WindowPtr win);
static void DoEventLoop(WindowPtr mainWindow);

/* Public function */
void getUserGridInput(double *gridData)
{
  int i;
  WindowPtr mainWindow;
  GrafPtr oldPort;

  /* Initialize QuickDraw resources in order to work with a GUI */
  InitGraf(&sysPort);
  SetPort(&sysPort);
  InitFonts();
  InitWindows();
  InitMenus();
  TEInit();
  InitDialogs(NULL);
  InitCursor();

  /* Initialize grid */
  for (i = 0; i < GRID_SIZE * GRID_SIZE; i++)
  {
    userGrid[i] = 0.0;
  }

  mainWindow = CreateMainWindow();
  ShowWindow(mainWindow);
  GetPort(&oldPort);
  SetPort(mainWindow);
  DoEventLoop(mainWindow);
  SetPort(oldPort);

  /* Copy data */
  for (i = 0; i < GRID_SIZE * GRID_SIZE; i++)
  {
    gridData[i] = userGrid[i];
  }
}

static WindowPtr CreateMainWindow(void)
{
  Rect wRect;
  WindowPtr win;

  SetRect(&wRect, 50, 50, 50 + GRID_SIZE * CELL_SIZE + 2 * LEFT_MARGIN,
          50 + GRID_SIZE * CELL_SIZE + 2 * TOP_MARGIN);

  win = NewWindow(NULL, &wRect, "\p8x8 Grid", TRUE, documentProc,
                  (WindowPtr)-1, TRUE, 0);
  return win;
}

static void DrawGrid(WindowPtr win)
{
  Rect cellRect;
  int row, col, idx;

  SetPort(win);
  EraseRect(&win->portRect);

  for (row = 0; row < GRID_SIZE; row++)
  {
    for (col = 0; col < GRID_SIZE; col++)
    {
      int left = LEFT_MARGIN + col * CELL_SIZE;
      int top = TOP_MARGIN + row * CELL_SIZE;
      int right = left + CELL_SIZE;
      int bottom = top + CELL_SIZE;

      SetRect(&cellRect, left, top, right, bottom);
      idx = row * GRID_SIZE + col;

      if (userGrid[idx] > 0.5)
      {
        PenPat(&blackPattern);
        PaintRect(&cellRect);
      }
      else
      {
        PenPat(&whitePattern);
        PaintRect(&cellRect);
      }

      PenNormal();
      FrameRect(&cellRect);
    }
  }
}

static void HandleMouseDown(EventRecord *theEvent, WindowPtr win)
{
  Point localPt;
  WindowPtr whichWin;
  short partCode;
  int col, row, idx;

  localPt = theEvent->where;
  partCode = FindWindow(localPt, &whichWin);

  if (partCode == inContent)
  {
    SetPort(win);
    GlobalToLocal(&localPt);

    col = (localPt.h - LEFT_MARGIN) / CELL_SIZE;
    row = (localPt.v - TOP_MARGIN) / CELL_SIZE;

    if (col >= 0 && col < GRID_SIZE && row >= 0 && row < GRID_SIZE)
    {
      idx = row * GRID_SIZE + col;
      userGrid[idx] = (userGrid[idx] > 0.5) ? 0.0 : 1.0;
      DrawGrid(win);
    }
  }
}

static void DoEventLoop(WindowPtr mainWindow)
{
  int done = 0;
  EventRecord event;

  ShowWindow(mainWindow);
  SetPort(mainWindow);
  DrawGrid(mainWindow);

  while (!done)
  {
    if (WaitNextEvent(everyEvent, &event, 30UL, NULL))
    {
      if (event.what == mouseDown)
      {
        HandleMouseDown(&event, mainWindow);
      }
      else if (event.what == keyDown || event.what == autoKey)
      {
        if ((event.message & charCodeMask) == '\r')
        {
          done = 1;
        }
      }
    }
  }

  DisposeWindow(mainWindow);
}