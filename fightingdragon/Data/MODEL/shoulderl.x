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
 24;
 -5.41432;-1.46496;-1.33480;,
 -5.41432;0.47391;-1.33480;,
 0.64181;0.28469;-1.33480;,
 0.03287;-0.57448;-1.33480;,
 -5.41432;1.56378;0.63798;,
 -5.41432;0.47391;-1.33480;,
 -5.41432;-1.46496;-1.33480;,
 -5.41432;-2.55483;0.63798;,
 0.64181;1.16183;0.63798;,
 -5.41432;1.56378;0.63798;,
 0.03287;-0.66325;0.63798;,
 0.03287;-0.57448;-1.33480;,
 0.64181;0.28469;-1.33480;,
 0.64181;1.16183;0.63798;,
 -5.41432;-2.55483;0.63798;,
 0.03287;-0.66325;0.63798;,
 -5.41432;-1.57789;2.61076;,
 0.03287;-0.58368;2.61076;,
 0.64181;0.37557;2.61076;,
 -5.41432;0.58684;2.61076;,
 -5.41432;-1.57789;2.61076;,
 -5.41432;0.58684;2.61076;,
 0.64181;0.37557;2.61076;,
 0.03287;-0.58368;2.61076;;
 
 10;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,2,1,9;,
 4;10,11,12,13;,
 4;14,0,3,15;,
 4;16,17,18,19;,
 4;4,7,20,21;,
 4;13,4,21,22;,
 4;10,13,22,23;,
 4;7,10,23,20;;
 
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
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTUREmurabito.png";
   }
  }
 }
 MeshNormals {
  15;
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.049316;0.998562;-0.021006;,
  0.634992;-0.772502;-0.005145;,
  0.000000;0.000000;1.000000;,
  0.043312;0.894536;-0.444893;,
  0.624416;-0.772877;-0.112986;,
  0.890090;-0.452145;0.057485;,
  0.897310;-0.441392;0.002599;,
  0.245750;-0.969257;-0.012165;,
  0.232291;-0.937092;-0.260575;,
  0.045922;0.912326;0.406882;,
  0.901677;-0.429236;-0.052296;,
  0.638111;-0.763037;0.102904;,
  0.243746;-0.940433;0.237011;;
  10;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,5,5,2;,
  4;3,6,7,8;,
  4;9,10,6,3;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;2,2,11,11;,
  4;3,8,12,13;,
  4;9,3,13,14;;
 }
 MeshTextureCoords {
  24;
  0.300188;0.743685;,
  0.300188;0.723315;,
  0.219971;0.725303;,
  0.228037;0.734329;,
  0.253019;0.752855;,
  0.253019;0.756854;,
  0.253019;0.763967;,
  0.253019;0.767966;,
  0.219971;0.716088;,
  0.300188;0.711865;,
  0.234686;0.761026;,
  0.234686;0.760700;,
  0.232637;0.757548;,
  0.232637;0.754330;,
  0.300188;0.755135;,
  0.228037;0.735262;,
  0.300188;0.744871;,
  0.228037;0.734426;,
  0.219971;0.724348;,
  0.300188;0.722129;,
  0.253019;0.764382;,
  0.253019;0.756440;,
  0.232637;0.757215;,
  0.234686;0.760734;;
 }
}
