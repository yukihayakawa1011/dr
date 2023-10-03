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
 28;
 -1.39245;-5.99994;-1.13436;,
 -1.96963;-5.99994;0.00892;,
 -1.96963;0.01686;0.00892;,
 -1.39245;0.01686;-1.13436;,
 -1.96963;-5.99994;0.00892;,
 -1.39245;-5.99994;1.15219;,
 -1.39245;0.01686;1.15219;,
 -1.96963;0.01686;0.00892;,
 0.00100;-5.99994;1.62575;,
 0.00100;0.01686;1.62575;,
 1.39445;-5.99994;1.15219;,
 1.39445;0.01686;1.15219;,
 1.97164;-5.99994;0.00892;,
 1.97164;0.01686;0.00892;,
 1.97164;-5.99994;0.00892;,
 1.39445;-5.99994;-1.13436;,
 1.39445;0.01686;-1.13436;,
 1.97164;0.01686;0.00892;,
 0.00100;-5.99994;-1.60792;,
 0.00100;0.01686;-1.60792;,
 -1.39245;-5.99994;-1.13436;,
 0.00100;-5.99994;0.00892;,
 1.39445;-5.99994;-1.13436;,
 0.00100;-5.99994;-1.60792;,
 -1.39245;0.01686;-1.13436;,
 0.00100;0.01686;0.00892;,
 1.39445;0.01686;-1.13436;,
 0.00100;0.01686;-1.60792;;
 
 24;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;5,8,9,6;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;14,15,16,17;,
 4;15,18,19,16;,
 4;18,0,3,19;,
 3;4,20,21;,
 3;5,4,21;,
 3;8,5,21;,
 3;10,8,21;,
 3;12,10,21;,
 3;22,12,21;,
 3;23,22,21;,
 3;20,23,21;,
 3;24,7,25;,
 3;7,6,25;,
 3;6,9,25;,
 3;9,11,25;,
 3;11,13,25;,
 3;13,26,25;,
 3;26,27,25;,
 3;27,24,25;;
 
 MeshMaterialList {
  3;
  24;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
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
 }
 MeshNormals {
  10;
  -0.655950;0.000000;-0.754804;,
  -1.000000;0.000000;0.000002;,
  -0.655949;0.000000;0.754806;,
  0.000000;0.000000;1.000000;,
  0.655946;0.000000;0.754808;,
  1.000000;0.000000;0.000002;,
  0.655947;0.000000;-0.754807;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;;
  24;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,0,0,7;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;;
 }
 MeshTextureCoords {
  28;
  0.398885;0.699348;,
  0.403733;0.699348;,
  0.403733;0.656617;,
  0.398885;0.656617;,
  0.401384;0.736925;,
  0.398631;0.736925;,
  0.398631;0.717716;,
  0.401384;0.717716;,
  0.391984;0.736925;,
  0.391984;0.717716;,
  0.385337;0.736925;,
  0.385337;0.717716;,
  0.382584;0.736925;,
  0.382584;0.717716;,
  0.370632;0.699348;,
  0.375480;0.699348;,
  0.375480;0.656617;,
  0.370632;0.656617;,
  0.387183;0.699348;,
  0.387183;0.656617;,
  0.398631;0.736925;,
  0.391984;0.736925;,
  0.385337;0.736925;,
  0.391984;0.736925;,
  0.398631;0.717716;,
  0.391984;0.717716;,
  0.385337;0.717716;,
  0.391984;0.717716;;
 }
}
