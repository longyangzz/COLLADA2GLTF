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


#ifndef __COLLADAMAX_GEOMETRYEXPORTER_H__
#define __COLLADAMAX_GEOMETRYEXPORTER_H__

#include "COLLADAMaxPrerequisites.h"

#include "COLLADAStreamWriter.h"
#include "COLLADALibraryGeometries.h"
#include "COLLADAPrimitves.h"

#include "COLLADAMaxGeometriesExporter.h"

namespace COLLADAMax
{

    class ExportNode;

    /** Class to export a single geometry.*/

    class GeometryExporter
    {

    private:
        /** List of channels.*/
        typedef std::vector<int> ChannelList;

        /** List of max materials.*/
        typedef std::vector<Mtl*> MaterialList;

    public:
        /** Symbol used for simple color materials.*/
        static const String COLOR_MATERIAL_SYMBOL;

    private:
        /** The export node which geoemetry should be exported.*/
        ExportNode * mExportNode;

        /** The id of the geometry.*/
        String mId;

        GeometriesExporter * mGeometriesExporter;

        DocumentExporter * mDocumentExporter;

        /** The geometry as a PolyObject.*/
        PolyObject * mPolyObject;

        /** The geometry as a TriObject.*/
        TriObject * mTriObject;

        /** The geometry as a GeomObject.*/
        GeomObject * mGeomObject;

        /** True if object must be deleted by us.*/
        bool mDeleteObject;

        static const String SYMBOL_NAME_PREFIX;

    public:
        /** Constructor
        @param exportNode The node which geometry should be exported
        @param geometriesExporter The geometries exporter
        @param documentExporter The document exporter this exporter belongs to
        */
        GeometryExporter ( ExportNode * exportNode, GeometriesExporter * geometriesExporter, DocumentExporter * documentExporter );

        /** Exports the geometry.*/
        void doExport();

        /** Returns the suffix of a texture that corresponds to channel @a channel.*/
        static String getTextureSourceIdSuffix ( int channel );


    private:
        GeometryExporter ( const GeometryExporter & geometryExporter );
        GeometryExporter & operator= ( const GeometryExporter & geometryExporter );

        /** Retrieves the base object and its super class id.*/
        void GeometryExporter::getBaseObjectAndID ( Object*& object, SClass_ID& sid );

        /** Classifies the object, i.e. check if it is a triObject or a polyObject.*/
        void GeometryExporter::classifyObject ( Object* object /*, bool affectsControllers*/ );

        /** Returns true if the current geometry is an editable polygon, false if it is a triangle mesh.*/
        bool isEditablePoly()
        {
            return mTriObject == 0;
        }

        /** Exports all the geometries in @a node and all its child nodes.*/
        void doExport ( const ExportNode* exportNode );

        /** Exports the positions of the mesh mesh.*/
        void exportPositions();

        /** Exports the normals of the mesh.*/
        void exportNormals();

        /** Exports the normals of a triangle mesh.*/
        void exportTriangleMeshNormals();

        /** Exports the normals of a editable poly mesh. */
        void exportEditablePolyNormals();

        /** Exports the textures of @a mesh.*/
        void exportTextures ( const ChannelList & channelList );

        /** Exports the texture channel of @a mesh.*/
        void exportTextureChannel ( int channelIndex );

        /** Exports the vertices element.*/
        void exportVertices ( const String & meshId );

        /** Exports the mesh as triangles.*/
        void exportTriangles ( const String & symbol, unsigned long numberOfFaces, int matId, size_t numMaterials, const ChannelList & channelList );

        /** Exports the mesh as a polylist.*/
        void exportPolylist ( const String & symbol, COLLADA::Polylist & polylist, int matId, size_t numMaterials, const ChannelList & channelList );

        /** Create list of materials used by this geometry.*/
        void flattenMaterials ( Mtl* material, MaterialList& mtlMap, int materialIndex = -1 );
    };

}

#endif //__COLLADAMAX_GEOMETRYEXPORTER_H__




