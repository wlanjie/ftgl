/*
 * FTGL - OpenGL font library
 *
 * Copyright (c) 2001-2004 Henry Maddocks <ftgl@opengl.geek.nz>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __ftgl__
#   warning This header is deprecated. Please use <FTGL/ftgl.h> from now.
#   include <FTGL/ftgl.h>
#endif

#ifndef __FTFont__
#define __FTFont__

#ifdef __cplusplus

class FTFontImpl;

/**
 * FTFont is the public interface for the FTGL library.
 *
 * Specific font classes are derived from this class. It uses the helper
 * classes FTFace and FTSize to access the Freetype library. This class
 * is abstract and deriving classes must implement the protected
 * <code>MakeGlyph</code> function to create glyphs of the
 * appropriate type.
 *
 * It is good practice after using these functions to test the error
 * code returned. <code>FT_Error Error()</code>. Check the freetype file
 * fterrdef.h for error definitions.
 *
 * @see     FTFace
 * @see     FTSize
 */
class FTGL_EXPORT FTFont
{
        /* Allow FTLayout classes to access this->impl. */
        friend class FTLayoutImpl;

    protected:
        FTFont();

        virtual ~FTFont();

    public:
        /**
         * Attach auxilliary file to font e.g font metrics.
         *
         * Note: not all font formats implement this function.
         *
         * @param fontFilePath  auxilliary font file path.
         * @return          <code>true</code> if file has been attached
         *                  successfully.
         */
        bool Attach(const char* fontFilePath);

        /**
         * Attach auxilliary data to font e.g font metrics, from memory
         *
         * Note: not all font formats implement this function.
         *
         * @param pBufferBytes  the in-memory buffer
         * @param bufferSizeInBytes  the length of the buffer in bytes
         * @return          <code>true</code> if file has been attached
         *                  successfully.
         */
        bool Attach(const unsigned char *pBufferBytes,
                    size_t bufferSizeInBytes);

        /**
         * Set the character map for the face.
         *
         * @param encoding      Freetype enumerate for char map code.
         * @return              <code>true</code> if charmap was valid and
         *                      set correctly
         */
        bool CharMap(FT_Encoding encoding);

        /**
         * Get the number of character maps in this face.
         *
         * @return character map count.
         */
        unsigned int CharMapCount();

        /**
         * Get a list of character maps in this face.
         *
         * @return pointer to the first encoding.
         */
        FT_Encoding* CharMapList();

        /**
         * Set the char size for the current face.
         *
         * @param size      the face size in points (1/72 inch)
         * @param res       the resolution of the target device.
         * @return          <code>true</code> if size was set correctly
         */
        bool FaceSize(const unsigned int size, const unsigned int res = 72);

        /**
         * Get the current face size in points.
         *
         * @return face size
         */
        unsigned int FaceSize() const;

        /**
         * Set the extrusion distance for the font. Only implemented by
         * FTGLExtrdFont
         *
         * @param depth  The extrusion distance.
         */
        void Depth(float depth);

        /**
         * Set the outset distance for the font. Only implemented by
         * FTGLOutlineFont, FTGLPolygonFont and FTGLExtrdFont
         *
         * @param outset  The outset distance.
         */
        void Outset(float outset);

        /**
         * Set the front and back outset distances for the font. Only
         * implemented by FTGLExtrdFont
         *
         * @param front  The front outset distance.
         * @param back   The back outset distance.
         */
        void Outset(float front, float back);

        /**
         * Enable or disable the use of Display Lists inside FTGL
         *
         * @param  useList <code>true</code> turns ON display lists.
         *                 <code>false</code> turns OFF display lists.
         */
        void UseDisplayList(bool useList);

        /**
         * Get the global ascender height for the face.
         *
         * @return  Ascender height
         */
        float Ascender() const;

        /**
         * Gets the global descender height for the face.
         *
         * @return  Descender height
         */
        float Descender() const;

        /**
         * Gets the line spacing for the font.
         *
         * @return  Line height
         */
        float LineHeight() const;

        /**
         * Get the bounding box for a string.
         *
         * @param string    a char buffer
         * @param start     The index of the first character of string
         *                  to check.
         * @param end       The index of the last character of string to
         *                  check.  If < 0 then characters will be parsed
         *                  until a '\0' is encountered.
         * @param llx       lower left near x coord
         * @param lly       lower left near y coord
         * @param llz       lower left near z coord
         * @param urx       upper right far x coord
         * @param ury       upper right far y coord
         * @param urz       upper right far z coord
         */
        void BBox(const char *string, const int start, const int end,
                  float& llx, float& lly, float& llz,
                  float& urx, float& ury, float& urz);

        /**
         * Get the bounding box for a string.
         *
         * @param string    a wchar_t buffer
         * @param start     The index of the first character of string
         *                  to check.
         * @param end       The index of the last character of string
         *                  to check.    If < 0 then characters will
         *                  be parsed until a '\0' is encountered.
         * @param llx       lower left near x coord
         * @param lly       lower left near y coord
         * @param llz       lower left near z coord
         * @param urx       upper right far x coord
         * @param ury       upper right far y coord
         * @param urz       upper right far z coord
         */
        void BBox(const wchar_t *string, const int start, const int end,
                  float& llx, float& lly, float& llz,
                  float& urx, float& ury, float& urz);

        /**
         * Get the bounding box for a string.
         *
         * @param string    a char string
         * @param llx       lower left near x coord
         * @param lly       lower left near y coord
         * @param llz       lower left near z coord
         * @param urx       upper right far x coord
         * @param ury       upper right far y coord
         * @param urz       upper right far z coord
         */
        void BBox(const char* string, float& llx, float& lly, float& llz,
                  float& urx, float& ury, float& urz);

        /**
         * Get the bounding box for a string.
         *
         * @param string    a wchar_t string
         * @param llx       lower left near x coord
         * @param lly       lower left near y coord
         * @param llz       lower left near z coord
         * @param urx       upper right far x coord
         * @param ury       upper right far y coord
         * @param urz       upper right far z coord
         */
        void BBox(const wchar_t* string, float& llx, float& lly, float& llz,
                  float& urx, float& ury, float& urz);

        /**
         * Get the advance width for a string.
         *
         * @param string    a wchar_t string
         * @return      advance width
         */
        float Advance(const wchar_t* string);

        /**
         * Get the advance width for a string.
         *
         * @param string    a char string
         * @return      advance width
         */
        float Advance(const char* string);

        /**
         * Render a string of characters
         *
         * @param string    'C' style string to be output.
         */
        void Render(const char* string);

        /**
         * Render a string of characters
         *
         * @param string    'C' style string to be output.
         * @param renderMode    Render mode to display
         */
        void Render(const char* string, int renderMode);

        /**
         * Render a string of characters
         *
         * @param string    wchar_t string to be output.
         */
        void Render(const wchar_t* string);

        /**
         * Render a string of characters
         *
         * @param string    wchar_t string to be output.
         * @param renderMode    Render mode to display
         */
        void Render(const wchar_t *string, int renderMode);

        /**
         * Queries the Font for errors.
         *
         * @return  The current error code.
         */
        FT_Error Error() const;

    protected:
        FTFontImpl *impl;
};

#endif //__cplusplus

FTGL_BEGIN_C_DECLS

FTGL_EXPORT void ftglDestroyFont(FTGLfont*);

FTGL_EXPORT int ftglAttachFile (FTGLfont*, const char*);
FTGL_EXPORT int ftglAttachData (FTGLfont*, const unsigned char *, size_t);

FTGL_EXPORT int          ftglCharMap      (FTGLfont*, FT_Encoding);
FTGL_EXPORT unsigned int ftglCharMapCount (FTGLfont*);
FTGL_EXPORT FT_Encoding* CharMapList      (FTGLfont*);

FTGL_EXPORT int          ftglSetFaceSize    (FTGLfont*, unsigned int);
FTGL_EXPORT int          ftglSetFaceSizeRes (FTGLfont*,
                                             unsigned int, unsigned int);
FTGL_EXPORT unsigned int ftglGetFaceSize    (FTGLfont*);
FTGL_EXPORT void         ftglSetDepth       (FTGLfont*, float);
FTGL_EXPORT void         ftglSetOutset      (FTGLfont*, float, float);

FTGL_EXPORT void ftglUseDisplayList (FTGLfont*, int);

FTGL_EXPORT float ftglAscender   (FTGLfont*);
FTGL_EXPORT float ftglDescender  (FTGLfont*);
FTGL_EXPORT float ftglLineHeight (FTGLfont*);
FTGL_EXPORT void  ftglBBox       (FTGLfont*, const char *, float[]);
FTGL_EXPORT float ftglAdvance    (FTGLfont*, const char *);
FTGL_EXPORT void  ftglRender     (FTGLfont*, const char *);
FTGL_EXPORT void  ftglRenderMode (FTGLfont*, const char *, int);

FTGL_EXPORT FT_Error ftglError (FTGLfont*);

FTGL_END_C_DECLS

#endif  //  __FTFont__
