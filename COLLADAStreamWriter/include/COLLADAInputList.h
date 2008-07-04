/*
    Copyright (c) 2008 NetAllied Systems GmbH
	
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/


#ifndef __COLLADASTREAMWRITER_INPUT_LIST_H__
#define __COLLADASTREAMWRITER_INPUT_LIST_H__

#include "COLLADAPrerequisites.h"
#include "COLLADAElementWriter.h"

namespace COLLADA
{

    class InputList;

    class PrimitivesBase;

    class Vertices;

    /** The geometry source data types. */
    enum Semantics
    {
        POSITION = 0, /**< Used for position data. */
        VERTEX, /**< Used to input the vertex sources within a polygon set. */
        NORMAL, /**< Used for surface normal vectors. */
        GEOTANGENT, /**< Used for surface tangent vectors. */
        GEOBINORMAL, /**< Used for surface binormal vectors. */
        TEXCOORD, /**< Used for texture coordinates. */
        TEXTANGENT, /**< Used for texture-aligned surface tangent vectors. */
        TEXBINORMAL, /**< Used for texture-aligned surface binormal vectors. */
        UV, /**< Used for generic mapping parameters. Do not confuse this with TEXCOORD. */
        COLOR, /**< Used for vertex colors. */
        EXTRA, /**< Used for application-specific vertex data. This is Maya-specific to support blind data. */

        POINT_SIZE, /**< Used to define the size of the Billboard generated by a given point.
     This is a type::POINTS specific type.  If the size is 0, a single pixel pt is rendered. */
        POINT_ROTATION, /**< Used to give a billboard orientation.  This is a type::POINTS
      specific type, and is not compulsory */
        UNKNOWN = -1, /**< An unknown data source. */
    };

    /** A class that holds information about an @a \<input\> element.*/

    class Input
    {

    public:
        /** Constructor
        @param semantic The semantic of the @a \<input\> element.
        @param source The source of the @a \<input\> element.
        @param offset The offset of the @a \<input\> element.
        @param set The set of the @a \<input\> element.
        */
        Input ( Semantics semantic, const String & source, int offset = -1, int set = -1 )
                : mSemantic ( semantic ),
                mSource ( source ),
                mOffset ( offset ),
                mSet ( set ) {}

        virtual ~Input() {}

        /** Returns the semantic of the Input*/
        Semantics getSemantic() const
        {
            return mSemantic;
        }

        /** Returns the source of the Input*/
        String getSource() const
        {
            return mSource;
        }

        /** Returns the offset of the Input*/
        int getOffset() const
        {
            return mOffset;
        }

        /** Returns the set of the Input*/
        int getSet() const
        {
            return mSet;
        }

    private:
        Semantics mSemantic;
        String mSource;
        int mOffset;
        int mSet;
    };


    /** A class that writes a list of Input objects to the stream.*/
    class InputList : public ElementWriter
    {

    public:
        /** Constructor
        @param The stream the InputList should be written to*/
        InputList ( StreamWriter * streamWriter ) : ElementWriter ( streamWriter ) {}

        /** Destructor*/
        ~InputList() {}

        /** Adds @a input to list of inputs that should be added*/
        void push_back ( Input input )
        {
            mList.push_back ( input );
        }

    private:
        friend PrimitivesBase;
        friend Vertices;

        /** List of all the inputs*/
        typedef std::list<Input> List;
        List mList;

        /** Add all the inputs, added using push_back(), to the stream*/
        void add();

        /** Returns a string containing the semantic name*/
        const String & getSemanticString ( Semantics semantic );
    };


} //namespace COLLADA



#endif //__COLLADASTREAMWRITER_INPUT_LIST_H__
