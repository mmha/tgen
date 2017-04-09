#include "tgen_debug.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>


// local utility definitions
namespace
{

    //-------------------------------------------------------------------------    

    void writeX3DTriIndexArray(const std::vector<tgen::VIndexT> & elements,
                               std::stringstream & ss)
    {
        if (elements.empty())
        {
            return;
        }

        ss << elements[0];

        for (std::size_t i = 1; i < elements.size(); ++i)
        {
            ss << " " << elements[i];

            if (i % 3 == 2)
            {
                ss << " -1";
            }
        }
    }

    //-------------------------------------------------------------------------

    void writeX3DArray(const std::vector<tgen::RealT> & elements,
                       std::stringstream              & ss)
    {
        if (elements.empty())
        {
            return;
        }

        ss << elements[0];

        for (std::size_t i = 1; i < elements.size(); ++i)
        {
            ss << " " << elements[i];
        }
    }

    //-------------------------------------------------------------------------

    void writeX3DLinesVCount(std::size_t numLines, std::stringstream & ss)
    {
        if (numLines == 0)
        {
            return;
        }
        
        ss << "2";

        for (std::size_t i = 1; i < numLines; ++i)
        {
            ss << " 2";
        }
    }

    //-------------------------------------------------------------------------

    void writeX3DVecFieldLineData(const std::vector<tgen::RealT> & pos3D,
                                  const std::vector<tgen::RealT> & dir3D,
                                  double                           vScale,
                                  std::stringstream              & ss)
    {
        if (pos3D.empty())
        {
            return;
        }

        ss << pos3D[0] << " " << pos3D[1] << " " << pos3D[2] << " " <<
              pos3D[0] + vScale * dir3D[0] << " " <<
              pos3D[1] + vScale * dir3D[1] << " " <<
              pos3D[2] + vScale * dir3D[2];

        for (std::size_t i = 3; i < pos3D.size(); i += 3)
        {
            ss << " ";
            ss << pos3D[i] << " " << pos3D[i+1] << " " << pos3D[i+2] << " " <<
                  pos3D[i]   + vScale * dir3D[i]   << " " <<
                  pos3D[i+1] + vScale * dir3D[i+1] << " " <<
                  pos3D[i+2] + vScale * dir3D[i+2];
        }
    }

    //-------------------------------------------------------------------------

    void writeX3DVecFieldVis(const std::vector<tgen::RealT> & pos3D,
                             const std::vector<tgen::RealT> & dir3D,
                             const std::string              & colorStr,
                             double                           vScale,
                             std::stringstream              & ss       )
    {
        ss << "    <Shape>" << '\n';
        ss << "      <Appearance>" << '\n';
        ss << "        <Material emissiveColor=\"" << colorStr << "\"/>"
                            << '\n';                
        ss << "      </Appearance>" << '\n';
        ss << "      <LineSet vertexCount=\"";
                            writeX3DLinesVCount(pos3D.size() / 3, ss);
                            ss << "\" >"
                            << '\n';
        ss << "        <Coordinate point=\"";
                            writeX3DVecFieldLineData(pos3D, dir3D, vScale, ss);
                            ss << "\"/>" << '\n';
        ss << "      </LineSet>" << '\n';
        ss << "    </Shape>" << '\n';
    }

    //-------------------------------------------------------------------------

} //anonymous namespace


namespace tgen
{

    //-------------------------------------------------------------------------

    void dumpDebugX3D(const std::vector<tgen::VIndexT> & triIndicesPos,
                      const std::vector<tgen::VIndexT> & triIndicesUV,
                      const std::vector<tgen::RealT>   & positions3D,
                      const std::vector<tgen::RealT>   & normals3D,
                      const std::vector<tgen::RealT>   & uvs2D,
                      const std::vector<tgen::RealT>   & tangents3D,
                      const std::vector<tgen::RealT>   & bitangents3D,
                      const char                       * filename      )
    {
        if (positions3D.empty())
        {
            return;
        }


        // guess a reasonable scale factor that will be used to adjust the size
        // of the visualized vectors
        tgen::RealT bbMin[3], bbMax[3];
        
        bbMin[0] = bbMax[0] = positions3D[0];
        bbMin[1] = bbMax[1] = positions3D[1];
        bbMin[2] = bbMax[2] = positions3D[2];

        for (std::size_t i = 0; i < positions3D.size(); i += 3)
        {
            for (std::size_t j = 0; j < 3; ++j)
            {
                bbMin[j] = std::min(positions3D[i+j], bbMin[j]);
                bbMax[j] = std::max(positions3D[i+j], bbMax[j]);
            }
        }

        tgen::RealT bbDiagLen = 0;
        for (std::size_t i = 0; i < 3; ++i)
        {
            tgen::RealT componentSize = bbMax[i] - bbMin[i];
            bbDiagLen += componentSize * componentSize;
        }

        bbDiagLen = std::sqrt(bbDiagLen);
                
        tgen::RealT vScale = bbDiagLen * 0.02;


        // write X3D file

        std::stringstream sstr;

        // prologue
        sstr << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << '\n';
        sstr << "<!DOCTYPE X3D PUBLIC \"ISO//Web3D//DTD X3D 3.0//EN\" "
             <<   "\"http://www.web3d.org/specifications/x3d-3.0.dtd\">"
             << '\n';
        sstr << "<X3D>" << '\n';
        sstr << "  <Scene>" << '\n';

        // textured object
        sstr << "    <Shape>" << '\n';
        sstr << "      <Appearance>" << '\n';
        sstr << "        <Material/>" << '\n';        
        sstr << "        <ImageTexture url=\"checker.png\">" << '\n';
        sstr << "          <TextureProperties magnificationFilter=\"NEAREST_PIXEL\"/>" << '\n';
        sstr << "        </ImageTexture>" << '\n';
        sstr << "      </Appearance>" << '\n';
        sstr << "      <IndexedFaceSet solid=\"false\"" << '\n';
        sstr << "                      coordIndex   =\"";
                                            writeX3DTriIndexArray(triIndicesPos, sstr);
                                            sstr << "\"" << '\n';
        sstr << "                      texCoordIndex=\"";
                                            writeX3DTriIndexArray(triIndicesUV, sstr);
                                            sstr << "\">" << '\n';
        sstr << "        <Coordinate        point=\"";
                                            writeX3DArray(positions3D, sstr);
                                            sstr << "\"/>" << '\n';
        sstr << "        <Normal            vector=\"";
                                            writeX3DArray(normals3D, sstr);
                                            sstr << "\"/>" << '\n';
        sstr << "        <TextureCoordinate point=\"";
                                            writeX3DArray(uvs2D, sstr);
                                            sstr << "\"/>" << '\n';
        sstr << "      </IndexedFaceSet>" << '\n';
        sstr << "    </Shape>" << '\n';

        // vector field visualizations
        writeX3DVecFieldVis(positions3D, normals3D,    "0 0 1", vScale, sstr);
        writeX3DVecFieldVis(positions3D, tangents3D,   "1 0 0", vScale, sstr);
        writeX3DVecFieldVis(positions3D, bitangents3D, "0 1 0", vScale, sstr);

        // epilogue
        sstr << "  </Scene>" << '\n';
        sstr << "</X3D>"     << '\n';


        std::ofstream fstr(filename);
        fstr << sstr.str() << '\n';
    }

    //-------------------------------------------------------------------------    

} //namespace tgen
