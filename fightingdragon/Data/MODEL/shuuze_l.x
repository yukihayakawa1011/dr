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
 100;
 -0.00661;-0.43156;-5.28500;,
 1.83268;-0.43156;-4.18305;,
 1.83268;-2.48467;-4.18305;,
 -0.00661;-2.48467;-5.28500;,
 2.59453;-0.43156;-1.52272;,
 2.59453;-2.48467;-1.52272;,
 1.83268;-0.82722;1.13762;,
 1.83268;-2.48467;1.13762;,
 -0.00661;-0.82722;2.23956;,
 -0.00661;-2.48467;2.23956;,
 -1.84589;-0.82722;1.13762;,
 -1.84589;-2.48467;1.13762;,
 -2.60775;-0.43156;-1.52272;,
 -2.60775;-2.48467;-1.52272;,
 -1.84589;-0.43156;-4.18305;,
 -1.84589;-2.48467;-4.18305;,
 -0.00661;-0.43156;-5.28500;,
 -0.00661;-2.48467;-5.28500;,
 -0.00661;-0.43156;-1.52272;,
 -0.00661;-0.43156;-1.52272;,
 -0.00661;-0.43156;-1.52272;,
 -0.00661;-0.43156;-1.52272;,
 -0.00661;-0.43156;-1.52272;,
 -0.00661;-0.43156;-1.52272;,
 -0.00661;-0.43156;-1.52272;,
 -0.00661;-0.43156;-1.52272;,
 -0.00661;-2.48467;-1.52272;,
 -0.00661;-2.48467;-1.52272;,
 -0.00661;-2.48467;-1.52272;,
 -0.00661;-2.48467;-1.52272;,
 -0.00661;-2.48467;-1.52272;,
 -0.00661;-2.48467;-1.52272;,
 -0.00661;-2.48467;-1.52272;,
 -0.00661;-2.48467;-1.52272;,
 -0.14930;0.03747;-2.05618;,
 1.24872;0.03747;-1.48854;,
 1.24872;-1.70766;-1.48854;,
 -0.14930;-1.70766;-2.05618;,
 0.96912;0.03747;-1.21446;,
 -0.14930;0.03747;-1.66857;,
 -0.14930;-1.70766;-1.66857;,
 0.96912;-1.70766;-1.21446;,
 1.82781;0.03747;-0.11813;,
 1.82781;-1.70766;-0.11813;,
 1.43238;0.03747;-0.11813;,
 1.43238;-1.70766;-0.11813;,
 1.24872;0.03747;1.25228;,
 1.24872;-1.70766;1.25228;,
 0.96912;0.03747;0.97820;,
 0.96912;-1.70766;0.97820;,
 -0.14930;0.03747;1.81993;,
 -0.14930;-1.70766;1.81993;,
 -0.14930;0.03747;1.43232;,
 -0.14930;-1.70766;1.43232;,
 -1.54733;0.03747;1.25228;,
 -1.54733;-1.70766;1.25228;,
 -1.26772;0.03747;0.97820;,
 -1.26772;-1.70766;0.97820;,
 -2.12641;0.03747;-0.11813;,
 -2.12641;-1.70766;-0.11813;,
 -1.73099;0.03747;-0.11813;,
 -1.73099;-1.70766;-0.11813;,
 -1.54733;0.03747;-1.48854;,
 -1.54733;-1.70766;-1.48854;,
 -1.26772;0.03747;-1.21445;,
 -1.26772;-1.70766;-1.21445;,
 -0.14930;0.03747;-2.05618;,
 -0.14930;-1.70766;-2.05618;,
 -0.14930;0.03747;-1.66857;,
 -0.14930;-1.70766;-1.66857;,
 0.96912;0.03747;-1.21446;,
 1.24872;0.03747;-1.48854;,
 -0.14930;-1.70766;-2.05618;,
 1.24872;-1.70766;-1.48854;,
 0.96912;-1.70766;-1.21446;,
 -0.14930;-1.70766;-1.66857;,
 1.43238;0.03747;-0.11813;,
 1.82781;0.03747;-0.11813;,
 1.82781;-1.70766;-0.11813;,
 1.43238;-1.70766;-0.11813;,
 0.96912;0.03747;0.97820;,
 1.24872;0.03747;1.25228;,
 1.24872;-1.70766;1.25228;,
 0.96912;-1.70766;0.97820;,
 -0.14930;0.03747;1.43232;,
 -0.14930;0.03747;1.81993;,
 -0.14930;-1.70766;1.81993;,
 -0.14930;-1.70766;1.43232;,
 -1.26772;0.03747;0.97820;,
 -1.54733;0.03747;1.25228;,
 -1.54733;-1.70766;1.25228;,
 -1.26772;-1.70766;0.97820;,
 -1.73099;0.03747;-0.11813;,
 -2.12641;0.03747;-0.11813;,
 -2.12641;-1.70766;-0.11813;,
 -1.73099;-1.70766;-0.11813;,
 -1.26772;0.03747;-1.21445;,
 -1.54733;0.03747;-1.48854;,
 -1.54733;-1.70766;-1.48854;,
 -1.26772;-1.70766;-1.21445;;
 
 56;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 4;34,35,36,37;,
 4;38,39,40,41;,
 4;35,42,43,36;,
 4;44,38,41,45;,
 4;42,46,47,43;,
 4;48,44,45,49;,
 4;46,50,51,47;,
 4;52,48,49,53;,
 4;50,54,55,51;,
 4;56,52,53,57;,
 4;54,58,59,55;,
 4;60,56,57,61;,
 4;58,62,63,59;,
 4;64,60,61,65;,
 4;62,66,67,63;,
 4;68,64,65,69;,
 4;34,39,70,71;,
 4;72,73,74,75;,
 4;71,70,76,77;,
 4;73,78,79,74;,
 4;77,76,80,81;,
 4;78,82,83,79;,
 4;81,80,84,85;,
 4;82,86,87,83;,
 4;85,84,88,89;,
 4;86,90,91,87;,
 4;89,88,92,93;,
 4;90,94,95,91;,
 4;93,92,96,97;,
 4;94,98,99,95;,
 4;97,96,39,34;,
 4;98,72,75,99;;
 
 MeshMaterialList {
  4;
  56;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
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
 }
 MeshNormals {
  33;
  -0.000000;0.998011;0.063036;,
  0.513939;0.000000;-0.857827;,
  0.793067;0.000000;-0.609134;,
  1.000000;0.000000;-0.000000;,
  0.793067;0.000000;0.609135;,
  0.513935;0.000000;0.857829;,
  -0.793066;0.000000;0.609136;,
  -1.000000;0.000000;-0.000000;,
  -0.793067;0.000000;-0.609134;,
  0.000000;-1.000000;-0.000000;,
  0.000001;0.000000;-1.000000;,
  0.702100;0.000000;-0.712079;,
  1.000000;0.000000;-0.000000;,
  0.702102;0.000000;0.712077;,
  0.000001;0.000000;1.000000;,
  -0.702103;0.000000;0.712075;,
  -1.000000;0.000000;0.000000;,
  -0.702101;0.000000;-0.712078;,
  0.000004;0.000000;1.000000;,
  -0.702102;0.000000;0.712076;,
  -0.702105;0.000000;-0.712074;,
  0.000000;0.000000;-1.000000;,
  0.702102;0.000000;-0.712076;,
  1.000000;0.000000;0.000002;,
  0.702101;0.000000;0.712078;,
  -0.513937;0.000000;0.857828;,
  -0.513941;0.000000;-0.857826;,
  0.000000;1.000000;0.000000;,
  0.000000;0.997276;0.073755;,
  0.031291;0.991557;0.125836;,
  -0.000000;0.994516;0.104588;,
  -0.031291;0.991557;0.125836;,
  0.000000;0.997276;0.073755;;
  56;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;25,6,6,25;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,26,26,8;,
  3;0,27,27;,
  3;0,28,27;,
  3;0,29,28;,
  3;0,30,29;,
  3;0,31,30;,
  3;0,32,31;,
  3;0,27,32;,
  3;0,27,27;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,11,11,10;,
  4;19,18,18,19;,
  4;11,12,12,11;,
  4;16,19,19,16;,
  4;12,13,13,12;,
  4;20,16,16,20;,
  4;13,14,14,13;,
  4;21,20,20,21;,
  4;14,15,15,14;,
  4;22,21,21,22;,
  4;15,16,16,15;,
  4;23,22,22,23;,
  4;16,17,17,16;,
  4;24,23,23,24;,
  4;17,10,10,17;,
  4;18,24,24,18;,
  4;27,27,27,27;,
  4;9,9,9,9;,
  4;27,27,27,27;,
  4;9,9,9,9;,
  4;27,27,27,27;,
  4;9,9,9,9;,
  4;27,27,27,27;,
  4;9,9,9,9;,
  4;27,27,27,27;,
  4;9,9,9,9;,
  4;27,27,27,27;,
  4;9,9,9,9;,
  4;27,27,27,27;,
  4;9,9,9,9;,
  4;27,27,27,27;,
  4;9,9,9,9;;
 }
 MeshTextureCoords {
  100;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
