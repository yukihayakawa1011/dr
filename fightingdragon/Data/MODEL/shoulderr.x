xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 20;
 6.22097;-1.46496;-1.33480;,
 0.77377;-0.57448;-1.33480;,
 0.16484;0.28469;-1.33480;,
 6.22097;0.47391;-1.33480;,
 6.22097;1.56378;0.63798;,
 6.22097;-2.55483;0.63798;,
 6.22097;-1.46496;-1.33480;,
 6.22097;0.47391;-1.33480;,
 0.16484;1.16183;0.63798;,
 6.22097;1.56378;0.63798;,
 0.77377;-0.66325;0.63798;,
 0.16484;1.16183;0.63798;,
 0.16484;0.28469;-1.33480;,
 0.77377;-0.57448;-1.33480;,
 6.22097;-2.55483;0.63798;,
 0.77377;-0.66325;0.63798;,
 6.22097;-1.57789;2.61076;,
 6.22097;0.58684;2.61076;,
 0.16484;0.37557;2.61076;,
 0.77377;-0.58368;2.61076;;
 
 10;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,3,2;,
 4;10,11,12,13;,
 4;14,15,1,0;,
 4;16,17,18,19;,
 4;4,17,16,5;,
 4;11,18,17,4;,
 4;10,19,18,11;,
 4;5,16,19,10;;
 
 MeshMaterialList {
  5;
  10;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "UV_Grid.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\murabito.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\murabito.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\murabito.png";
   }
  }
 }
 MeshNormals {
  15;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  -0.049316;0.998562;-0.021007;,
  -0.634994;-0.772500;-0.005145;,
  0.000000;0.000000;1.000000;,
  -0.043313;0.894536;-0.444893;,
  -0.897313;-0.441387;0.002598;,
  -0.890093;-0.452140;0.057484;,
  -0.624419;-0.772875;-0.112986;,
  -0.245750;-0.969257;-0.012165;,
  -0.232291;-0.937092;-0.260576;,
  -0.045922;0.912326;0.406882;,
  -0.638113;-0.763035;0.102905;,
  -0.901680;-0.429230;-0.052295;,
  -0.243745;-0.940433;0.237011;;
  10;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,5,5;,
  4;3,6,7,8;,
  4;9,3,8,10;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;2,11,11,2;,
  4;3,12,13,6;,
  4;9,14,12,3;;
 }
 MeshTextureCoords {
  20;
  0.130038;0.746965;,
  0.197957;0.736959;,
  0.205550;0.727304;,
  0.130038;0.725178;,
  0.183979;0.752855;,
  0.183979;0.767966;,
  0.183979;0.763967;,
  0.183979;0.756854;,
  0.205550;0.717447;,
  0.130038;0.712931;,
  0.202311;0.761026;,
  0.204361;0.754330;,
  0.204361;0.757548;,
  0.202311;0.760700;,
  0.130038;0.759212;,
  0.197957;0.737956;,
  0.183979;0.764382;,
  0.183979;0.756440;,
  0.204361;0.757215;,
  0.202311;0.760734;;
 }
}
