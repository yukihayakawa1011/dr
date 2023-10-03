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
 82;
 0.01606;-0.01522;-0.00000;,
 1.28934;-0.01522;-1.26694;,
 0.01606;-0.01522;-1.79172;,
 1.81674;-0.01522;-0.00000;,
 1.28934;-0.01522;1.26694;,
 0.01606;-0.01522;1.79172;,
 -1.25721;-0.01522;1.26694;,
 -1.78462;-0.01522;0.00000;,
 -1.25721;-0.01522;-1.26694;,
 1.41115;-0.16746;-1.38815;,
 0.01606;-0.16746;-1.96314;,
 1.98902;-0.16746;-0.00000;,
 1.41115;-0.16746;1.38815;,
 0.01606;-0.16746;1.96314;,
 -1.37903;-0.16746;1.38815;,
 -1.95690;-0.16746;0.00000;,
 -1.37903;-0.16746;-1.38815;,
 1.51442;-0.60101;-1.49091;,
 0.01606;-0.60101;-2.10846;,
 2.13506;-0.60101;-0.00000;,
 1.51442;-0.60101;1.49091;,
 0.01606;-0.60101;2.10846;,
 -1.48230;-0.60101;1.49091;,
 -2.10294;-0.60101;0.00000;,
 -1.48230;-0.60101;-1.49091;,
 1.58342;-1.24986;-1.55956;,
 0.01606;-1.24986;-2.20556;,
 2.23265;-1.24986;-0.00000;,
 1.58342;-1.24986;1.55956;,
 0.01606;-1.24986;2.20556;,
 -1.55130;-1.24986;1.55956;,
 -2.20053;-1.24986;0.00000;,
 -1.55130;-1.24986;-1.55956;,
 1.60765;-2.01522;-1.58368;,
 0.01606;-2.01522;-2.23966;,
 2.26692;-2.01522;-0.00000;,
 1.60765;-2.01522;1.58368;,
 0.01606;-2.01522;2.23966;,
 -1.57553;-2.01522;1.58367;,
 -2.23479;-2.01522;0.00000;,
 -1.57553;-2.01522;-1.58368;,
 1.28769;-13.59523;-1.27163;,
 0.01606;-13.59523;-1.79835;,
 1.81441;-13.59523;-0.00000;,
 1.28769;-13.59523;1.27163;,
 0.01606;-13.59523;1.79835;,
 -1.25557;-13.59523;1.27163;,
 -1.78229;-13.59523;0.00000;,
 -1.25557;-13.59523;-1.27163;,
 1.26833;-14.36060;-1.25227;,
 0.01606;-14.36060;-1.77097;,
 1.78703;-14.36060;-0.00000;,
 1.26833;-14.36060;1.25227;,
 0.01606;-14.36060;1.77097;,
 -1.23621;-14.36060;1.25227;,
 -1.75491;-14.36060;0.00000;,
 -1.23621;-14.36060;-1.25227;,
 1.21320;-15.00944;-1.19714;,
 0.01606;-15.00944;-1.69300;,
 1.70907;-15.00944;-0.00000;,
 1.21320;-15.00944;1.19714;,
 0.01606;-15.00944;1.69300;,
 -1.18108;-15.00944;1.19714;,
 -1.67695;-15.00944;0.00000;,
 -1.18108;-15.00944;-1.19714;,
 1.13069;-15.44299;-1.11463;,
 0.01606;-15.44299;-1.57632;,
 1.59238;-15.44299;-0.00000;,
 1.13069;-15.44299;1.11463;,
 0.01606;-15.44299;1.57632;,
 -1.09857;-15.44299;1.11463;,
 -1.56026;-15.44299;0.00000;,
 -1.09857;-15.44299;-1.11463;,
 1.03336;-15.59523;-1.01730;,
 0.01606;-15.59523;-1.43868;,
 1.45474;-15.59523;-0.00000;,
 1.03336;-15.59523;1.01730;,
 0.01606;-15.59523;1.43868;,
 -1.00124;-15.59523;1.01730;,
 -1.42262;-15.59523;0.00000;,
 -1.00124;-15.59523;-1.01730;,
 0.01606;-15.59523;-0.00000;;
 
 88;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 4;42,41,49,50;,
 4;41,43,51,49;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,42,50,56;,
 4;50,49,57,58;,
 4;49,51,59,57;,
 4;51,52,60,59;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,50,58,64;,
 4;58,57,65,66;,
 4;57,59,67,65;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,58,66,72;,
 4;66,65,73,74;,
 4;65,67,75,73;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,66,74,80;,
 3;74,73,81;,
 3;73,75,81;,
 3;75,76,81;,
 3;76,77,81;,
 3;77,78,81;,
 3;78,79,81;,
 3;79,80,81;,
 3;80,74,81;;
 
 MeshMaterialList {
  4;
  88;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
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
  82;
  0.000000;1.000000;0.000000;,
  0.000000;0.937213;-0.348758;,
  0.245649;0.937440;-0.246705;,
  0.347535;0.937667;0.000000;,
  0.245649;0.937440;0.246705;,
  0.000000;0.937213;0.348758;,
  -0.245645;0.937441;0.246703;,
  -0.347527;0.937670;0.000000;,
  -0.245645;0.937441;-0.246703;,
  0.000000;0.555247;-0.831686;,
  0.586527;0.556115;-0.588831;,
  0.830521;0.556988;0.000000;,
  0.586527;0.556115;0.588831;,
  0.000000;0.555247;0.831686;,
  -0.586524;0.556120;0.588830;,
  -0.830516;0.556995;0.000000;,
  -0.586524;0.556120;-0.588830;,
  0.000000;0.234042;-0.972227;,
  0.686135;0.234588;-0.688613;,
  0.971963;0.235136;0.000000;,
  0.686135;0.234588;0.688613;,
  0.000000;0.234042;0.972227;,
  -0.686135;0.234587;0.688613;,
  -0.971963;0.235136;0.000000;,
  -0.686135;0.234587;-0.688613;,
  0.000000;0.096421;-0.995341;,
  0.702548;0.096659;-0.705041;,
  0.995294;0.096899;0.000000;,
  0.702548;0.096659;0.705042;,
  -0.000001;0.096420;0.995341;,
  -0.702549;0.096655;0.705041;,
  -0.995295;0.096895;0.000000;,
  -0.702549;0.096658;-0.705041;,
  0.000000;0.003171;-0.999995;,
  0.706165;0.003033;-0.708041;,
  0.999996;0.002895;0.000000;,
  0.706165;0.003033;0.708041;,
  -0.000001;0.003162;0.999995;,
  -0.706167;0.003022;0.708039;,
  -0.999996;0.002891;0.000001;,
  -0.706166;0.003032;-0.708040;,
  -0.000000;-0.036973;-0.999316;,
  0.706305;-0.037157;-0.706932;,
  0.999303;-0.037341;-0.000000;,
  0.706305;-0.037157;0.706932;,
  -0.000001;-0.036980;0.999316;,
  -0.706306;-0.037164;0.706931;,
  -0.999303;-0.037341;0.000000;,
  -0.706305;-0.037157;-0.706931;,
  -0.000000;-0.077616;-0.996983;,
  0.704973;-0.077615;-0.704974;,
  0.996984;-0.077613;-0.000000;,
  0.704973;-0.077615;0.704974;,
  -0.000000;-0.077616;0.996983;,
  -0.704973;-0.077615;0.704974;,
  -0.996984;-0.077613;0.000000;,
  -0.704973;-0.077615;-0.704974;,
  -0.000000;-0.190223;-0.981741;,
  0.694194;-0.190225;-0.694197;,
  0.981740;-0.190225;-0.000000;,
  0.694194;-0.190225;0.694197;,
  -0.000000;-0.190223;0.981741;,
  -0.694194;-0.190225;0.694197;,
  -0.981741;-0.190225;0.000000;,
  -0.694194;-0.190225;-0.694197;,
  -0.000000;-0.481614;-0.876384;,
  0.619695;-0.481617;-0.619696;,
  0.876381;-0.481618;-0.000000;,
  0.619695;-0.481617;0.619696;,
  -0.000000;-0.481614;0.876384;,
  -0.619695;-0.481617;0.619696;,
  -0.876381;-0.481618;0.000000;,
  -0.619695;-0.481617;-0.619696;,
  -0.000000;-0.917978;-0.396632;,
  0.280461;-0.917978;-0.280461;,
  0.396632;-0.917978;-0.000000;,
  0.280461;-0.917978;0.280461;,
  -0.000000;-0.917978;0.396632;,
  -0.280461;-0.917978;0.280461;,
  -0.396632;-0.917978;0.000000;,
  -0.280461;-0.917978;-0.280461;,
  0.000000;-1.000000;-0.000000;;
  88;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,49,57,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,57,65,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,65,73,80;,
  3;73,74,81;,
  3;74,75,81;,
  3;75,76,81;,
  3;76,77,81;,
  3;77,78,81;,
  3;78,79,81;,
  3;79,80,81;,
  3;80,73,81;;
 }
 MeshTextureCoords {
  82;
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
