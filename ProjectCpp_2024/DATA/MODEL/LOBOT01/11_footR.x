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
 126;
 3.94883;-4.79161;-9.32103;,
 3.94883;-7.54911;-14.78608;,
 2.12959;-6.31379;-14.78608;,
 2.12959;-3.04670;-9.38337;,
 -2.06280;-6.31379;-14.78608;,
 -2.06280;-3.04670;-9.38337;,
 -3.88204;-7.54911;-14.78608;,
 -3.88204;-4.79161;-9.38337;,
 3.94883;-10.30661;-18.28662;,
 2.12959;-9.58089;-18.28662;,
 -2.06280;-9.58089;-18.28662;,
 -3.88204;-10.30661;-18.28662;,
 3.94883;-13.06410;-17.99923;,
 2.12959;-12.84797;-17.99923;,
 -2.06280;-12.84797;-17.99923;,
 -3.88204;-13.06410;-17.99923;,
 -3.88204;-4.79161;-9.38337;,
 -3.88204;-7.54911;-14.78608;,
 -3.88204;-7.54911;-6.71673;,
 -3.88204;-4.79161;-6.71673;,
 -3.88204;-7.54911;-2.59424;,
 -3.88204;-5.83056;-4.23176;,
 -3.88204;-7.54911;1.57451;,
 -3.88204;-6.80945;1.57451;,
 -3.88204;-10.30661;-18.28662;,
 -3.88204;-10.30661;-6.71673;,
 -3.88204;-10.30661;-2.54496;,
 -3.88204;-10.30661;1.62378;,
 -3.88204;-13.06410;-17.99923;,
 -3.88204;-13.06410;-6.71673;,
 -3.88204;-13.06410;-2.54496;,
 -3.88204;-13.06410;1.71067;,
 -3.88204;-6.80945;1.57451;,
 -3.88204;-7.54911;1.57451;,
 -2.06280;-6.31379;1.57451;,
 -2.06280;-5.43743;1.57451;,
 2.12959;-6.31379;1.57451;,
 2.12959;-5.43743;1.57451;,
 3.94883;-7.54911;1.57451;,
 3.94883;-6.80945;1.57451;,
 -3.88204;-10.30661;1.62378;,
 -2.06280;-9.58089;1.62378;,
 2.12959;-9.58089;1.62378;,
 3.94883;-10.30661;1.62378;,
 -3.88204;-13.06410;1.71067;,
 -2.06280;-12.84797;1.71067;,
 2.12959;-12.84797;1.71067;,
 3.94883;-13.06410;1.71067;,
 3.94883;-6.80945;1.57451;,
 3.94883;-7.54911;1.57451;,
 3.94883;-7.54911;-2.59424;,
 3.94883;-5.83056;-4.23176;,
 3.94883;-7.54911;-6.71673;,
 3.94883;-4.79161;-6.71673;,
 3.94883;-7.54911;-14.78608;,
 3.94883;-4.79161;-9.32103;,
 3.94883;-10.30661;1.62378;,
 3.94883;-10.30661;-2.54496;,
 3.94883;-10.30661;-6.71673;,
 3.94883;-10.30661;-18.28662;,
 3.94883;-13.06410;1.71067;,
 3.94883;-13.06410;-2.54496;,
 3.94883;-13.06410;-6.71673;,
 3.94883;-13.06410;-17.99923;,
 3.94883;-5.83056;-4.23176;,
 2.12959;-4.27764;-4.23176;,
 2.12959;-5.43743;1.57451;,
 -2.06280;-4.27764;-4.23176;,
 -2.06280;-5.43743;1.57451;,
 -3.88204;-5.83056;-4.23176;,
 3.94883;-4.79161;-6.71673;,
 2.12959;-3.04670;-6.71673;,
 -2.06280;-3.04670;-6.71673;,
 -3.88204;-4.79161;-6.71673;,
 3.94883;-4.79161;-9.32103;,
 2.12959;-3.04670;-9.38337;,
 -2.06280;-3.04670;-9.38337;,
 -3.88204;-4.79161;-9.38337;,
 3.94883;-13.06410;-2.54496;,
 2.12959;-12.84797;1.71067;,
 2.12959;-12.84797;-2.54496;,
 -2.06280;-12.84797;1.71067;,
 -2.06280;-12.84797;-2.54496;,
 -3.88204;-13.06410;-2.54496;,
 3.94883;-13.06410;-6.71673;,
 2.12959;-12.84797;-6.71673;,
 -2.06280;-12.84797;-6.71673;,
 -3.88204;-13.06410;-6.71673;,
 3.94883;-13.06410;-17.99923;,
 2.12959;-12.84797;-17.99923;,
 -2.06280;-12.84797;-17.99923;,
 -3.88204;-13.06410;-17.99923;,
 -0.05859;1.02951;-1.63045;,
 -0.05859;-4.83668;-3.89813;,
 -1.67419;-5.10736;-3.39431;,
 -1.67419;0.75883;-1.12664;,
 -2.34338;-5.76083;-2.17801;,
 -2.34338;0.10536;0.08966;,
 -1.67419;-6.41431;-0.96170;,
 -1.67419;-0.54811;1.30597;,
 -0.05859;-6.68498;-0.45789;,
 -0.05859;-0.81878;1.80978;,
 1.55700;-6.41431;-0.96170;,
 1.55700;-0.54811;1.30597;,
 2.22620;-5.76083;-2.17801;,
 2.22620;0.10536;0.08966;,
 1.55700;-5.10736;-3.39431;,
 1.55700;0.75883;-1.12664;,
 -0.05859;-4.83668;-3.89813;,
 -0.05859;1.02951;-1.63045;,
 -0.05859;0.10536;0.08966;,
 -0.05859;0.10536;0.08966;,
 -0.05859;0.10536;0.08966;,
 -0.05859;0.10536;0.08966;,
 -0.05859;0.10536;0.08966;,
 -0.05859;0.10536;0.08966;,
 -0.05859;0.10536;0.08966;,
 -0.05859;0.10536;0.08966;,
 -0.05859;-5.76083;-2.17801;,
 -0.05859;-5.76083;-2.17801;,
 -0.05859;-5.76083;-2.17801;,
 -0.05859;-5.76083;-2.17801;,
 -0.05859;-5.76083;-2.17801;,
 -0.05859;-5.76083;-2.17801;,
 -0.05859;-5.76083;-2.17801;,
 -0.05859;-5.76083;-2.17801;;
 
 78;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;1,8,9,2;,
 4;2,9,10,4;,
 4;4,10,11,6;,
 4;8,12,13,9;,
 4;9,13,14,10;,
 4;10,14,15,11;,
 4;16,17,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;17,24,25,18;,
 4;18,25,26,20;,
 4;20,26,27,22;,
 4;24,28,29,25;,
 4;25,29,30,26;,
 4;26,30,31,27;,
 4;32,33,34,35;,
 4;35,34,36,37;,
 4;37,36,38,39;,
 4;33,40,41,34;,
 4;34,41,42,36;,
 4;36,42,43,38;,
 4;40,44,45,41;,
 4;41,45,46,42;,
 4;42,46,47,43;,
 4;48,49,50,51;,
 4;51,50,52,53;,
 4;53,52,54,55;,
 4;49,56,57,50;,
 4;50,57,58,52;,
 4;52,58,59,54;,
 4;56,60,61,57;,
 4;57,61,62,58;,
 4;58,62,63,59;,
 4;48,64,65,66;,
 4;66,65,67,68;,
 4;68,67,69,23;,
 4;64,70,71,65;,
 4;65,71,72,67;,
 4;67,72,73,69;,
 4;70,74,75,71;,
 4;71,75,76,72;,
 4;72,76,77,73;,
 4;78,60,79,80;,
 4;80,79,81,82;,
 4;82,81,31,83;,
 4;84,78,80,85;,
 4;85,80,82,86;,
 4;86,82,83,87;,
 4;88,84,85,89;,
 4;89,85,86,90;,
 4;90,86,87,91;,
 4;92,93,94,95;,
 4;95,94,96,97;,
 4;97,96,98,99;,
 4;99,98,100,101;,
 4;101,100,102,103;,
 4;103,102,104,105;,
 4;105,104,106,107;,
 4;107,106,108,109;,
 3;110,92,95;,
 3;111,95,97;,
 3;112,97,99;,
 3;113,99,101;,
 3;114,101,103;,
 3;115,103,105;,
 3;116,105,107;,
 3;117,107,109;,
 3;118,94,93;,
 3;119,96,94;,
 3;120,98,96;,
 3;121,100,98;,
 3;122,102,100;,
 3;123,104,102;,
 3;124,106,104;,
 3;125,108,106;;
 
 MeshMaterialList {
  6;
  78;
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
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
   0.432800;0.464000;0.496000;1.000000;;
   10.000000;
   0.490000;0.490000;0.490000;;
   0.297550;0.319000;0.341000;;
  }
  Material {
   0.316800;0.316800;0.316800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.178824;0.034510;0.059608;1.000000;;
   5.000000;
   0.110000;0.110000;0.110000;;
   0.134118;0.025882;0.044706;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.228800;0.257600;0.392000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.138400;0.210400;0.288800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  81;
  0.837120;0.527633;-0.144338;,
  0.349877;0.902907;-0.249691;,
  -0.348485;0.903199;-0.250579;,
  0.483215;0.716409;-0.503251;,
  0.248810;0.781988;-0.571479;,
  -0.247428;0.782018;-0.572037;,
  0.200270;0.348997;-0.915474;,
  0.099177;0.355342;-0.929460;,
  -0.099177;0.355342;-0.929460;,
  -0.023627;-0.095622;-0.995137;,
  -0.011814;-0.091632;-0.995723;,
  0.011814;-0.091632;-0.995723;,
  -0.836127;0.528818;-0.145748;,
  -0.915767;0.391939;0.088062;,
  -0.903388;0.409219;0.128180;,
  -0.480612;0.717076;-0.504790;,
  -1.000000;0.000000;0.000000;,
  -0.200270;0.348997;-0.915474;,
  0.023627;-0.095622;-0.995137;,
  -0.899892;0.428930;0.078826;,
  0.000000;-0.000000;1.000000;,
  -0.002171;0.007888;0.999967;,
  0.002171;0.007888;0.999967;,
  -0.003964;0.021795;0.999755;,
  0.003964;0.021795;0.999755;,
  -0.003587;0.027813;0.999607;,
  0.003587;0.027813;0.999607;,
  0.903388;0.409219;0.128180;,
  0.915767;0.391939;0.088062;,
  0.004341;0.008236;0.999957;,
  1.000000;0.000000;0.000000;,
  0.007928;0.022756;0.999710;,
  0.007173;0.029040;0.999552;,
  0.335228;0.895020;0.294213;,
  -0.335228;0.895020;0.294213;,
  0.363118;0.908023;0.208901;,
  -0.363118;0.908023;0.208901;,
  -0.059090;-0.998253;0.000000;,
  0.059090;-0.998253;-0.000000;,
  -0.059090;-0.998253;0.000000;,
  0.059090;-0.998253;-0.000000;,
  0.000000;0.880913;0.473278;,
  0.000001;0.360564;-0.932734;,
  -0.664730;0.269371;-0.696831;,
  -1.000000;0.000001;-0.000001;,
  -0.664730;-0.269371;0.696831;,
  0.000001;-0.360563;0.932735;,
  0.664728;-0.269371;0.696832;,
  1.000000;0.000001;-0.000001;,
  0.664729;0.269372;-0.696832;,
  -0.000000;-0.880912;-0.473280;,
  -0.004341;0.008236;0.999957;,
  -0.007928;0.022756;0.999710;,
  -0.007173;0.029040;0.999552;,
  0.899892;0.428930;0.078826;,
  0.327950;0.927627;0.178764;,
  -0.327950;0.927627;0.178764;,
  -0.117973;-0.993017;0.000000;,
  -0.117973;-0.993017;0.000000;,
  -0.059090;-0.998253;0.000000;,
  0.059090;-0.998253;-0.000000;,
  0.117973;-0.993017;-0.000000;,
  0.117973;-0.993017;-0.000000;,
  -0.117973;-0.993017;0.000000;,
  0.117973;-0.993017;-0.000000;,
  0.000000;0.880912;0.473281;,
  -0.000001;0.880912;0.473280;,
  0.000000;0.880913;0.473278;,
  -0.000001;0.880915;0.473275;,
  0.000000;0.880915;0.473274;,
  0.000001;0.880915;0.473275;,
  0.000000;0.880913;0.473278;,
  0.000001;0.880912;0.473280;,
  -0.000000;-0.880913;-0.473279;,
  0.000000;-0.880913;-0.473278;,
  0.000000;-0.880912;-0.473281;,
  0.000002;-0.880912;-0.473280;,
  -0.000000;-0.880913;-0.473278;,
  -0.000002;-0.880912;-0.473280;,
  0.000000;-0.880912;-0.473281;,
  0.000000;-0.880913;-0.473279;;
  78;
  4;0,3,4,1;,
  4;1,4,5,2;,
  4;2,5,15,12;,
  4;3,6,7,4;,
  4;4,7,8,5;,
  4;5,8,17,15;,
  4;6,9,10,7;,
  4;7,10,11,8;,
  4;8,11,18,17;,
  4;12,16,16,13;,
  4;13,16,16,14;,
  4;14,16,16,19;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;20,51,21,20;,
  4;20,21,22,20;,
  4;20,22,29,20;,
  4;51,52,23,21;,
  4;21,23,24,22;,
  4;22,24,31,29;,
  4;52,53,25,23;,
  4;23,25,26,24;,
  4;24,26,32,31;,
  4;54,30,30,27;,
  4;27,30,30,28;,
  4;28,30,30,0;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;54,27,33,55;,
  4;55,33,34,56;,
  4;56,34,14,19;,
  4;27,28,35,33;,
  4;33,35,36,34;,
  4;34,36,13,14;,
  4;28,0,1,35;,
  4;35,1,2,36;,
  4;36,2,12,13;,
  4;57,58,59,37;,
  4;37,59,60,38;,
  4;38,60,61,62;,
  4;63,57,37,39;,
  4;39,37,38,40;,
  4;40,38,62,64;,
  4;57,63,39,37;,
  4;37,39,40,38;,
  4;38,40,64,62;,
  4;42,42,43,43;,
  4;43,43,44,44;,
  4;44,44,45,45;,
  4;45,45,46,46;,
  4;46,46,47,47;,
  4;47,47,48,48;,
  4;48,48,49,49;,
  4;49,49,42,42;,
  3;41,65,66;,
  3;41,66,67;,
  3;41,67,68;,
  3;41,68,69;,
  3;41,69,70;,
  3;41,70,71;,
  3;41,71,72;,
  3;41,72,65;,
  3;50,73,74;,
  3;50,75,73;,
  3;50,76,75;,
  3;50,77,76;,
  3;50,78,77;,
  3;50,79,78;,
  3;50,80,79;,
  3;50,74,80;;
 }
 MeshTextureCoords {
  126;
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.666670;,
  0.333330;1.000000;,
  0.333330;0.666670;,
  0.666670;1.000000;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
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
  0.937500;1.000000;;
 }
}