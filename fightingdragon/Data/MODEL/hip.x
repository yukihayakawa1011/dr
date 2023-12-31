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
 35;
 0.05589;0.13746;-5.74107;,
 4.19297;0.13746;-4.80923;,
 4.28978;-11.60199;-4.54677;,
 -0.29397;-11.39919;-5.52980;,
 5.81067;0.13746;-0.09385;,
 5.99446;-11.60199;0.09188;,
 4.26013;0.13746;2.30345;,
 4.28978;-11.60199;2.23348;,
 -0.10047;0.13746;3.44021;,
 -1.59739;-11.39919;3.12057;,
 -4.41946;0.13746;2.06291;,
 -6.05559;-11.39919;1.91756;,
 -5.71951;0.13746;-0.09385;,
 -6.58884;-11.39919;0.09188;,
 -3.98174;0.13746;-3.99780;,
 -6.05559;-11.39919;-4.15991;,
 0.05589;0.13746;-5.74107;,
 -0.29397;-11.39919;-5.52980;,
 1.70606;-11.96305;-1.06715;,
 -1.59739;-11.96305;-1.54723;,
 3.13608;-11.47168;0.09188;,
 1.70606;-11.96305;1.25091;,
 -1.59739;-11.96305;1.73099;,
 -4.90084;-11.96305;1.25091;,
 -4.62340;-11.96305;0.09188;,
 -4.90084;-11.96305;-1.06715;,
 -1.59739;-11.96305;-1.54723;,
 -1.59739;-0.07314;-0.09385;,
 -1.59739;-0.07314;-0.09385;,
 -1.59739;-0.07314;-0.09385;,
 -1.59739;-0.07314;-0.09385;,
 -1.59739;-0.07314;-0.09385;,
 -1.59739;-0.07314;-0.09385;,
 -1.59739;-0.07314;-0.09385;,
 -1.59739;-0.07314;-0.09385;;
 
 24;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;3,2,18,19;,
 4;2,5,20,18;,
 4;5,7,21,20;,
 4;7,9,22,21;,
 4;9,11,23,22;,
 4;11,13,24,23;,
 4;13,15,25,24;,
 4;15,17,26,25;,
 3;19,18,27;,
 3;18,20,28;,
 3;20,21,29;,
 3;21,22,30;,
 3;22,23,31;,
 3;23,24,32;,
 3;24,25,33;,
 3;25,26,34;;
 
 MeshMaterialList {
  5;
  24;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.200800;0.200800;0.200800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.661600;0.455200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.147200;0.160000;0.545600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.520800;0.599200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.775200;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  29;
  -0.052268;0.001538;-0.998632;,
  0.661440;-0.009973;-0.749931;,
  0.990050;0.008688;0.140449;,
  0.543495;-0.008241;0.839372;,
  -0.042313;-0.003579;0.999098;,
  -0.658715;0.063524;0.749706;,
  -0.990768;0.115468;0.071036;,
  -0.720624;0.083195;-0.688316;,
  -0.015052;-0.989566;-0.143292;,
  0.053958;-0.997905;-0.035690;,
  0.092272;-0.995451;-0.023724;,
  0.057158;-0.990608;0.124213;,
  -0.030063;-0.919681;0.391513;,
  -0.219049;-0.946561;0.236727;,
  -0.320395;-0.947126;0.017300;,
  -0.172436;-0.982098;-0.075821;,
  -0.198566;-0.162095;0.966590;,
  0.000000;-0.121333;0.992612;,
  -0.365163;-0.176283;0.914101;,
  -0.566632;-0.222378;0.793395;,
  -0.558352;-0.244782;-0.792670;,
  -0.360156;-0.203046;-0.910527;,
  -0.195363;-0.190727;-0.962007;,
  0.000000;-0.151701;-0.988426;,
  0.142183;-0.150160;-0.978384;,
  0.944835;-0.236930;0.226166;,
  0.969108;-0.246637;0.000196;,
  0.943233;-0.243582;-0.225785;,
  0.142776;-0.120090;0.982442;;
  24;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,0,0,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,8,8,15;,
  3;17,18,16;,
  3;18,19,16;,
  3;20,21,22;,
  3;21,23,22;,
  3;23,24,22;,
  3;25,26,26;,
  3;26,27,26;,
  3;28,17,16;;
 }
 MeshTextureCoords {
  35;
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.375000;0.625000;,
  0.375000;0.750000;,
  0.500000;0.625000;,
  0.500000;0.750000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.750000;0.625000;,
  0.750000;0.750000;,
  0.875000;0.625000;,
  0.875000;0.750000;,
  1.000000;0.625000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
