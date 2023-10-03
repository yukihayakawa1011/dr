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
 172;
 0.03714;20.00069;-1.33081;,
 0.53855;19.36778;-1.76254;,
 0.03714;19.36778;-1.94137;,
 0.03714;20.00069;-1.33081;,
 0.74624;19.36778;-1.33081;,
 0.03714;20.00069;-1.33081;,
 0.53855;19.36778;-1.21632;,
 0.03714;20.00069;-1.33081;,
 0.03714;19.36778;-1.03749;,
 0.03714;20.00069;-1.33081;,
 -0.46428;19.36778;-1.21632;,
 0.03714;20.00069;-1.33081;,
 -0.67197;19.36778;-1.33081;,
 0.03714;20.00069;-1.33081;,
 -0.46428;19.36778;-1.76254;,
 0.03714;20.00069;-1.33081;,
 0.03714;19.36778;-1.94137;,
 0.87509;19.85001;-2.05185;,
 0.04073;19.85001;-2.33921;,
 1.22069;19.85001;-1.35809;,
 0.87509;19.85001;-1.02689;,
 0.04283;19.89646;-0.82768;,
 -0.79363;19.85001;-1.02689;,
 -1.13923;19.85001;-1.35809;,
 -0.79363;19.85001;-2.05185;,
 0.04073;19.85001;-2.33921;,
 4.98833;15.36024;-5.41469;,
 0.04750;15.36024;-7.49211;,
 7.03489;15.36024;-0.39937;,
 4.91983;15.32298;2.44469;,
 0.04749;15.36024;3.42719;,
 -4.89334;15.36024;2.54628;,
 -6.64509;15.35851;-0.40245;,
 -4.89334;15.36024;-5.41469;,
 0.04750;15.36024;-7.49211;,
 5.55094;9.21792;-0.46908;,
 4.05744;9.26206;-5.07907;,
 4.34615;9.21792;2.51839;,
 -0.01275;9.21792;3.28218;,
 -4.37164;9.21792;2.51839;,
 -5.74799;9.21792;-0.46908;,
 -4.37164;9.21792;-4.58103;,
 -0.01275;9.21792;-6.59593;,
 3.78074;3.74727;-4.65081;,
 -0.01145;3.57483;-6.02195;,
 5.15979;3.57483;-0.41876;,
 4.07635;3.57483;2.19844;,
 -0.01145;3.57483;2.98780;,
 -4.09926;3.57483;2.19843;,
 -5.35685;3.57483;-0.41876;,
 -4.09926;3.57483;-4.16042;,
 -0.01275;9.21792;-6.59593;,
 -0.01145;3.57483;-6.02195;,
 4.18114;0.01992;-4.77956;,
 0.02370;0.01992;-5.69547;,
 5.90320;0.01992;-0.09346;,
 4.18114;0.01992;2.22001;,
 0.03867;0.31129;3.61848;,
 -4.13373;0.01992;2.22001;,
 -5.85579;0.01992;-0.09346;,
 -4.13373;0.01992;-3.75442;,
 0.02370;0.01992;-5.69547;,
 2.27369;0.36028;-2.62956;,
 0.02370;0.36028;-3.68005;,
 3.20567;0.36028;-0.09346;,
 2.27369;0.36028;0.57907;,
 0.02370;0.36028;1.12050;,
 -2.22628;0.36028;0.57907;,
 -3.15826;0.36028;-0.09346;,
 -2.22628;0.36028;-2.62956;,
 0.02370;0.36028;-3.68005;,
 0.02370;-0.04783;-0.09346;,
 0.02370;-0.04783;-0.09346;,
 0.02370;-0.04783;-0.09346;,
 0.02370;-0.04783;-0.09346;,
 0.02370;-0.04783;-0.09346;,
 0.02370;-0.04783;-0.09346;,
 0.02370;-0.04783;-0.09346;,
 0.02370;-0.04783;-0.09346;,
 -0.01275;9.21792;-6.59593;,
 0.08570;12.54176;-5.42128;,
 0.04750;15.36024;-7.49211;,
 -2.43236;12.37965;-7.26561;,
 2.97616;12.85517;-6.10503;,
 -2.35344;16.85596;-4.48475;,
 -0.43318;16.26132;-6.39194;,
 -1.14993;16.04414;-7.07831;,
 -3.01561;16.86135;-5.68700;,
 -0.00001;13.40856;-5.81005;,
 -0.64162;13.31675;-6.96183;,
 -0.43318;10.55584;-6.39194;,
 -1.06468;10.68114;-7.07809;,
 -2.32101;9.77710;-4.32851;,
 -3.19978;9.68128;-6.07853;,
 -4.25213;10.52340;-3.29980;,
 -5.24962;10.77299;-5.07876;,
 -4.23308;12.98555;-2.29718;,
 -6.13436;13.45211;-4.61297;,
 -4.42031;15.99191;-3.43848;,
 -5.28528;16.08768;-5.02709;,
 -2.35344;16.85596;-4.48475;,
 -3.01561;16.86135;-5.68700;,
 -1.93904;15.42576;-7.47552;,
 -3.50792;16.26132;-6.71032;,
 -1.39228;13.31675;-8.17842;,
 -1.85379;11.29956;-7.47529;,
 -3.50792;10.55584;-6.71032;,
 -5.07681;11.39139;-5.94513;,
 -5.72666;13.40856;-5.62817;,
 -5.07681;15.42576;-5.94513;,
 -3.50792;16.26132;-6.71032;,
 -2.99060;14.50028;-7.80464;,
 -3.83967;14.95245;-7.39052;,
 -2.63890;13.40856;-7.97617;,
 -2.99060;12.31687;-7.80464;,
 -3.83967;11.86467;-7.39052;,
 -4.68874;12.31687;-6.97639;,
 -5.04044;13.40856;-6.80486;,
 -4.68874;14.50028;-6.97639;,
 -3.83967;14.95245;-7.39052;,
 -3.95616;13.40856;-7.62935;,
 -3.95616;13.40856;-7.62935;,
 -3.95616;13.40856;-7.62935;,
 -3.95616;13.40856;-7.62935;,
 -3.95616;13.40856;-7.62935;,
 -3.95616;13.40856;-7.62935;,
 -3.95616;13.40856;-7.62935;,
 -3.95616;13.40856;-7.62935;,
 2.33777;17.18223;-4.32257;,
 4.83178;16.26132;-3.64473;,
 5.28199;16.04414;-4.91652;,
 3.25902;17.13585;-5.96961;,
 5.73876;13.40856;-3.17258;,
 6.11993;13.40856;-4.48032;,
 4.83178;10.55584;-3.64473;,
 5.28199;10.77299;-4.91652;,
 2.37496;9.77710;-4.22226;,
 3.25902;9.68128;-5.96961;,
 0.39935;10.52340;-5.16270;,
 1.23605;10.77299;-7.02270;,
 0.20181;12.98555;-5.55148;,
 0.33536;13.45211;-7.45684;,
 0.41079;15.99191;-5.38038;,
 1.17330;16.08768;-7.02063;,
 2.33777;17.18223;-4.32257;,
 3.25902;17.13585;-5.96961;,
 5.13191;15.42576;-5.78712;,
 3.58360;16.26132;-6.59312;,
 5.97164;13.40856;-5.83438;,
 5.13191;11.39139;-5.78712;,
 3.58360;10.55584;-6.59312;,
 2.03528;11.39139;-7.39912;,
 1.39395;13.40856;-7.73297;,
 2.03528;15.42576;-7.39912;,
 3.58360;16.26132;-6.59312;,
 4.77098;14.50028;-6.82819;,
 3.93304;14.95245;-7.26439;,
 5.11807;13.40856;-6.64751;,
 4.77098;12.31687;-6.82819;,
 3.93304;11.86467;-7.26439;,
 3.09510;12.31687;-7.70059;,
 2.74801;13.40856;-7.88128;,
 3.09510;14.50028;-7.70059;,
 3.93304;14.95245;-7.26439;,
 4.05574;13.40856;-7.50010;,
 4.05574;13.40856;-7.50010;,
 4.05574;13.40856;-7.50010;,
 4.05574;13.40856;-7.50010;,
 4.05574;13.40856;-7.50010;,
 4.05574;13.40856;-7.50010;,
 4.05574;13.40856;-7.50010;,
 4.05574;13.40856;-7.50010;;
 
 135;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;26,28,35,36;,
 4;28,29,37,35;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,33,41,40;,
 4;42,36,43,44;,
 4;36,35,45,43;,
 4;35,37,46,45;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,51,52,50;,
 4;44,43,53,54;,
 4;43,45,55,53;,
 4;45,46,56,55;,
 4;46,47,57,56;,
 4;47,48,58,57;,
 4;48,49,59,58;,
 4;49,50,60,59;,
 4;50,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 3;63,62,71;,
 3;62,64,72;,
 3;64,65,73;,
 3;65,66,74;,
 3;66,67,75;,
 3;67,68,76;,
 3;68,69,77;,
 3;69,70,78;,
 3;79,80,81;,
 3;82,41,33;,
 3;82,51,41;,
 3;82,34,51;,
 3;82,33,34;,
 3;83,27,26;,
 3;83,42,27;,
 3;83,36,42;,
 3;83,26,36;,
 4;84,85,86,87;,
 4;85,88,89,86;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;87,86,102,103;,
 4;86,89,104,102;,
 4;89,91,105,104;,
 4;91,93,106,105;,
 4;93,95,107,106;,
 4;95,97,108,107;,
 4;97,99,109,108;,
 4;99,101,110,109;,
 4;103,102,111,112;,
 4;102,104,113,111;,
 4;104,105,114,113;,
 4;105,106,115,114;,
 4;106,107,116,115;,
 4;107,108,117,116;,
 4;108,109,118,117;,
 4;109,110,119,118;,
 3;112,111,120;,
 3;111,113,121;,
 3;113,114,122;,
 3;114,115,123;,
 3;115,116,124;,
 3;116,117,125;,
 3;117,118,126;,
 3;118,119,127;,
 4;128,129,130,131;,
 4;129,132,133,130;,
 4;132,134,135,133;,
 4;134,136,137,135;,
 4;136,138,139,137;,
 4;138,140,141,139;,
 4;140,142,143,141;,
 4;142,144,145,143;,
 4;131,130,146,147;,
 4;130,133,148,146;,
 4;133,135,149,148;,
 4;135,137,150,149;,
 4;137,139,151,150;,
 4;139,141,152,151;,
 4;141,143,153,152;,
 4;143,145,154,153;,
 4;147,146,155,156;,
 4;146,148,157,155;,
 4;148,149,158,157;,
 4;149,150,159,158;,
 4;150,151,160,159;,
 4;151,152,161,160;,
 4;152,153,162,161;,
 4;153,154,163,162;,
 3;156,155,164;,
 3;155,157,165;,
 3;157,158,166;,
 3;158,159,167;,
 3;159,160,168;,
 3;160,161,169;,
 3;161,162,170;,
 3;162,163,171;;
 
 MeshMaterialList {
  4;
  135;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
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
   0.200784;0.200784;0.200784;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.661961;0.454902;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.147451;0.160000;0.545882;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.520784;0.599216;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  153;
  0.231335;0.749819;-0.619884;,
  0.000002;0.694285;-0.719700;,
  0.459165;0.719339;-0.521267;,
  0.634148;0.710487;-0.305066;,
  0.367540;0.439444;0.819636;,
  0.000003;0.420485;0.907300;,
  -0.367537;0.439447;0.819636;,
  -0.424628;0.475751;0.770294;,
  -0.459160;0.719342;-0.521267;,
  0.000321;0.639282;0.768972;,
  -0.485353;0.672476;0.558757;,
  -0.668453;0.667897;0.327238;,
  -0.377145;0.490433;-0.785644;,
  0.000097;0.422616;-0.906309;,
  0.378310;0.485732;-0.788001;,
  0.495950;0.549086;-0.672709;,
  0.488177;0.668536;0.561020;,
  0.080297;0.261182;-0.961944;,
  0.487532;0.378178;-0.786952;,
  0.581784;0.808766;0.086164;,
  0.314699;0.526504;0.789783;,
  0.006156;0.361716;0.932268;,
  -0.513705;0.393169;0.762578;,
  -0.592157;0.802384;0.074363;,
  -0.551401;0.445137;-0.705556;,
  0.055405;-0.193161;-0.979601;,
  0.657854;-0.136937;-0.740592;,
  0.990487;-0.124981;0.057576;,
  0.604563;-0.077931;0.792736;,
  0.002816;-0.038506;0.999254;,
  -0.598186;-0.068875;0.798392;,
  -0.992793;-0.099040;0.067473;,
  -0.729072;-0.193772;-0.656435;,
  -0.055637;-0.077505;-0.995438;,
  0.704854;-0.010681;-0.709272;,
  0.997366;0.035018;0.063523;,
  0.620316;0.029799;0.783785;,
  0.000293;0.021727;0.999764;,
  -0.604464;0.017668;0.796436;,
  -0.997605;-0.003757;0.069072;,
  -0.733265;-0.059988;-0.677291;,
  -0.073247;-0.056669;-0.995703;,
  0.686562;0.070230;-0.723671;,
  0.985454;0.143533;0.090990;,
  0.606200;0.123350;0.785689;,
  0.000590;0.103224;0.994658;,
  -0.596009;0.099779;0.796754;,
  -0.994568;0.066325;0.080225;,
  -0.724750;-0.033830;-0.688181;,
  0.008396;-0.999765;0.019968;,
  0.002638;-0.999976;0.006349;,
  0.006242;-0.999821;0.017876;,
  0.011900;-0.996288;0.085254;,
  -0.000064;-0.990959;0.134166;,
  -0.011964;-0.996295;0.085171;,
  -0.003739;-0.999784;0.020433;,
  0.008257;-0.999841;0.015783;,
  -0.000000;-0.996411;0.084649;,
  -0.999093;0.015584;0.039640;,
  -0.372479;-0.138634;-0.917627;,
  0.377485;-0.118764;-0.918368;,
  -0.069140;0.996973;-0.035574;,
  0.152634;0.955128;-0.253837;,
  0.796276;0.001870;-0.604931;,
  0.806229;-0.060605;-0.588492;,
  -0.042494;-0.997885;-0.049188;,
  -0.641177;-0.675644;0.363864;,
  -0.830898;-0.012181;0.556291;,
  -0.600435;0.680794;0.419520;,
  -0.182088;0.928389;-0.323940;,
  0.287292;0.725131;-0.625818;,
  0.732112;0.004437;-0.681169;,
  0.513220;-0.327380;-0.793365;,
  -0.217024;-0.885308;-0.411255;,
  -0.787773;-0.611796;-0.071547;,
  -0.994882;-0.008509;0.100689;,
  -0.748118;0.663188;-0.022377;,
  -0.332760;0.644951;-0.687974;,
  0.103483;0.454947;-0.884485;,
  0.313321;0.003708;-0.949640;,
  0.079617;-0.408122;-0.909449;,
  -0.369395;-0.564133;-0.738446;,
  -0.753069;-0.392277;-0.528210;,
  -0.898329;-0.001465;-0.439321;,
  -0.739090;0.433684;-0.515426;,
  -0.412522;0.338329;-0.845789;,
  -0.214155;0.239595;-0.946959;,
  -0.170275;-0.000094;-0.985397;,
  -0.223405;-0.237601;-0.945323;,
  -0.415580;-0.336197;-0.845142;,
  -0.652939;-0.237398;-0.719245;,
  -0.747831;-0.000001;-0.663889;,
  -0.652937;0.237396;-0.719247;,
  -0.438374;-0.000001;-0.898793;,
  -0.005014;0.998158;-0.060461;,
  0.707305;0.681407;0.188159;,
  0.960050;-0.000001;0.279827;,
  0.697281;-0.688527;0.199321;,
  0.021876;-0.998576;-0.048652;,
  -0.704683;-0.656424;-0.269312;,
  -0.964852;-0.016086;-0.262302;,
  -0.753141;0.616390;-0.229873;,
  0.202358;0.883702;-0.422045;,
  0.788638;0.604599;-0.111851;,
  0.999646;-0.000001;0.026611;,
  0.785524;-0.609504;-0.107032;,
  0.212130;-0.886580;-0.411068;,
  -0.429311;-0.606583;-0.669141;,
  -0.457722;0.593831;-0.661706;,
  0.383082;0.563037;-0.732283;,
  0.739549;0.419425;-0.526450;,
  0.887277;-0.000001;-0.461237;,
  0.739548;-0.419423;-0.526453;,
  0.381082;-0.564689;-0.732054;,
  -0.023340;-0.392278;-0.919551;,
  -0.181199;-0.001465;-0.983445;,
  -0.016190;0.389154;-0.921030;,
  0.434516;0.338331;-0.834702;,
  0.630861;0.240037;-0.737832;,
  0.689689;-0.000001;-0.724106;,
  0.630863;-0.240038;-0.737831;,
  0.434515;-0.338333;-0.834702;,
  0.189786;-0.237401;-0.952692;,
  0.088840;-0.000001;-0.996046;,
  0.189788;0.237399;-0.952692;,
  0.461746;-0.000001;-0.887012;,
  0.000002;0.472518;0.881321;,
  0.424629;0.475746;0.770296;,
  -0.634143;0.710492;-0.305064;,
  -0.493874;0.554228;-0.670015;,
  0.672914;0.662321;0.329421;,
  -0.000068;0.751945;-0.659225;,
  0.437739;0.765678;-0.471297;,
  0.339607;0.734728;0.587232;,
  0.005765;0.687612;0.726056;,
  -0.344980;0.743500;0.572885;,
  -0.445038;0.765066;-0.465419;,
  0.922423;-0.187391;-0.337669;,
  0.980407;-0.180195;0.079568;,
  0.864369;-0.141016;0.482681;,
  -0.988913;-0.126984;0.076985;,
  -0.938262;-0.128943;-0.320996;,
  0.016647;-0.988130;0.152712;,
  -0.084827;-0.992087;0.092557;,
  -0.114177;-0.993059;-0.028243;,
  -0.077575;-0.993892;-0.078488;,
  -0.000126;-0.998495;-0.054839;,
  0.077449;-0.993889;-0.078652;,
  0.119189;-0.992600;-0.023207;,
  0.106431;-0.988079;0.111233;,
  0.782921;0.064338;-0.618785;,
  0.267615;-0.932917;-0.240930;,
  -0.253182;-0.002933;-0.967414;;
  135;
  3;0,2,1;,
  3;0,3,2;,
  3;126,4,127;,
  3;126,5,4;,
  3;126,6,5;,
  3;126,7,6;,
  3;128,8,128;,
  3;0,1,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;129,12,12,129;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;130,16,16,130;,
  4;16,9,9,16;,
  4;131,132,18,17;,
  4;132,19,19,18;,
  4;19,133,20,19;,
  4;133,134,21,20;,
  4;134,135,22,21;,
  4;135,23,23,22;,
  4;23,136,24,23;,
  4;136,131,17,24;,
  4;137,138,27,26;,
  4;138,139,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,140,31,30;,
  4;140,141,32,31;,
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
  4;142,143,50,49;,
  4;143,144,51,50;,
  4;144,145,52,51;,
  4;145,146,53,52;,
  4;146,147,54,53;,
  4;147,148,55,54;,
  4;148,149,56,55;,
  4;149,142,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  3;58,58,58;,
  3;59,32,24;,
  3;59,25,32;,
  3;59,17,25;,
  3;59,24,17;,
  3;60,17,18;,
  3;60,25,17;,
  3;60,26,25;,
  3;60,18,26;,
  4;61,62,70,69;,
  4;150,63,71,150;,
  4;63,64,72,71;,
  4;151,65,73,151;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,61,69,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,73,81,80;,
  4;73,74,82,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,69,77,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,81,89,88;,
  4;81,82,90,89;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;84,77,85,92;,
  3;85,86,93;,
  3;86,87,93;,
  3;87,88,93;,
  3;88,89,93;,
  3;89,90,93;,
  3;90,91,93;,
  3;91,92,93;,
  3;92,85,93;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,98,106,105;,
  4;98,99,107,106;,
  4;99,100,100,107;,
  4;100,101,108,100;,
  4;101,94,102,108;,
  4;102,103,110,109;,
  4;103,104,111,110;,
  4;104,105,112,111;,
  4;105,106,113,112;,
  4;106,107,114,113;,
  4;107,152,115,114;,
  4;152,108,116,115;,
  4;108,102,109,116;,
  4;109,110,118,117;,
  4;110,111,119,118;,
  4;111,112,120,119;,
  4;112,113,121,120;,
  4;113,114,122,121;,
  4;114,115,123,122;,
  4;115,116,124,123;,
  4;116,109,117,124;,
  3;117,118,125;,
  3;118,119,125;,
  3;119,120,125;,
  3;120,121,125;,
  3;121,122,125;,
  3;122,123,125;,
  3;123,124,125;,
  3;124,117,125;;
 }
 MeshTextureCoords {
  172;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.250000;0.500000;,
  0.125000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  0.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
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
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.938200;0.438200;,
  0.068590;0.431410;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.750000;0.500000;,
  0.750000;0.625000;,
  0.875000;0.500000;,
  0.875000;0.625000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
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
  0.937500;1.000000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.750000;0.500000;,
  0.750000;0.625000;,
  0.875000;0.500000;,
  0.875000;0.625000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
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