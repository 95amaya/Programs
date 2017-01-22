/*
 * File: extgraph.h
 * Last modified on Fri Jul 22 12:24:59 1994 by eroberts
 * -----------------------------------------------------
 * This interface is the extended graphics interface.
 * It includes all of the facilities in graphics.h, plus
 * several additional functions that are designed to
 * support more sophisticated, interactive graphics.
 */

#ifndef _extgraph_h
#define _extgraph_h

#include "genlib.h"

/* Exported functions */

/*
 * Section 1 -- Basic functions from graphics.h
 */

#include "graphics.h"

/*
 * Section 2 -- Elliptical arcs
 */

/*
 * Function: DrawEllipticalArc
 * Usage: DrawEllipticalArc(rx, ry, start, sweep);
 * -----------------------------------------------
 * This procedure draws an elliptical arc.  It is exactly
 * the same in its operation as DrawArc in the graphics.h
 * interface, except that the radius is different along the
 * two axes.
 */

void DrawEllipticalArc(double rx, double ry,
                       double start, double sweep);

/*
 * Section 3 -- Graphical regions
 */

/*
 * Functions: StartFilledRegion, EndFilledRegion
 * Usage: StartFilledRegion(grayScale);
 *        . . . other calls . . .
 *        EndFilledRegion();
 * ------------------------------
 * These calls make it possible to draw filled shapes on the
 * display.  After calling StartFilledRegion, any calls to
 * DrawLine and DrawArc are used to create a shape definition
 * and do not appear on the screen until EndFilledRegion is
 * called.  The lines and arcs must be consecutive, in the
 * sense that each new element must start where the last
 * one ended.  MovePen calls may occur at the beginning
 * or the end of the region, but not in the interior. When
 * EndFilledRegion is called, the entire region appears on the
 * screen, with its interior filled in.  The grayScale parameter
 * is a number between 0 and 1 and indicates how dark the fill
 * should be.  If grayScale is 1, the shape will be filled with
 * black.  At 0, the shape will be invisible.  In between, it
 * will be some gray shade.  The levels of gray scale available
 * will differ depending on the implementation.
 */

void StartFilledRegion(double grayScale);
void EndFilledRegion(void);

/*
 * Section 4 -- String functions
 */

/*
 * Function: DrawTextString
 * Usage: DrawTextString(text);
 * ----------------------------
 * This function displays the string text at the current point
 * in the current font and size.  The current point is updated
 * so that the next DrawTextString command would continue from
 * the next character position.  The string may not include the
 * newline character.
 */

void DrawTextString(string text);

/*
 * Function: TextStringWidth
 * Usage: w = TextStringWidth(text);
 * ---------------------------------
 * This function eturns the width of the text string if displayed
 * at the current font and size.
 */

double TextStringWidth(string text);

/*
 * Function: SetFont
 * Usage: SetFont(font);
 * ---------------------
 * This function sets a new font according to the font string,
 * which is case-independent.  Different systems support different
 * fonts, although common ones like "Times" and "Courier" are often
 * supported.  Initially, the font is set to "Default" which is
 * always supported, although the underlying font is system
 * dependent.  If the font name is unrecognized, no error is
 * generated, and the font remains unchanged.  If you need to
 * detect this condition, you can call GetFont to see if the
 * change took effect.  By not generating an error in this case,
 * programs become more portable.
 */

void SetFont(string font);

/*
 * Function: GetFont
 * Usage: font = GetFont();
 * ------------------------
 * This function returns the current font name as a string.
 */

string GetFont(void);

/*
 * Function: SetPointSize
 * Usage: SetPointSize(size);
 * --------------------------
 * This function sets a new point size.  If the point size is
 * not supported for a particular font, the closest existing
 * size is selected.
 */

void SetPointSize(int size);

/*
 * Function: GetPointSize
 * Usage: size = GetPointSize();
 * -----------------------------
 * This function returns the current point size.
 */

int GetPointSize(void);

/*
 * Section 5 -- Miscellaneous functions
 */

/*
 * Function: SetEraseMode
 * Usage: SetEraseMode(TRUE);
 *        SetEraseMode(FALSE);
 * ---------------------------
 * The SetEraseMode function sets the value of the internal
 * erasing flag.  If this is set, the graphics package erases
 * instead of drawing by drawing in white instead of black.
 * If erase mode is set to FALSE, normal drawing is restored.
 */

void SetEraseMode(bool mode);

/*
 * Function: GetEraseMode
 * Usage: mode = GetEraseMode();
 * -----------------------------
 * This function returns the current state of the erase mode flag.
 */

bool GetEraseMode(void);

/*
 * Function: SetWindowTitle
 * Usage: SetWindowTitle(title);
 * -----------------------------
 * This function sets the title of the graphics window, if such
 * an operation is possible on the display.  If it is not possible
 * for a particular implementation, the call is simply ignored.
 */

void SetWindowTitle(string title);

/*
 * Function: GetWindowTitle
 * Usage: title = GetWindowTitle();
 * --------------------------------
 * This function returns the title of the graphics window.  If the
 * implementation does not support titles, this call returns the
 * empty string.
 */

string GetWindowTitle(void);

/*
 * Function: UpdateDisplay
 * Usage: UpdateDisplay();
 * -----------------------
 * This function initiates an immediate update of the graphics
 * window and is necessary for animation.  Ordinarily, the
 * graphics window is updated only when the program waits for
 * user input.
 */

void UpdateDisplay(void);

/*
 * Function: Pause
 * Usage: Pause(seconds);
 * ----------------------
 * The Pause function updates the graphics window and then
 * pauses for the indicated number of seconds.  This function
 * is useful for animation where the motion would otherwise
 * be too fast.
 */

void Pause(double seconds);

/*
 * Functions: SaveGraphicsState, RestoreGraphicsState
 * Usage: SaveGraphicsState();
 *        . . . graphical operations . . .
 *        RestoreGraphicsState();
 * ---------------------------------------------------
 * The SaveGraphicsState function saves the current graphics
 * state (the current pen position, the font, the point size,
 * and the erase mode flag) internally, so that they can be
 * restored by the next RestoreGraphicsState call.  These two
 * functions must be used in pairs but may be nested to any depth.
 */

void SaveGraphicsState(void);
void RestoreGraphicsState(void);

#endif
