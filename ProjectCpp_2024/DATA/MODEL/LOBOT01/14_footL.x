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
 -3.97929;-4.87687;-9.44961;,
 -2.16005;-3.13196;-9.51195;,
 -2.16005;-6.39905;-14.91466;,
 -3.97929;-7.63437;-14.91466;,
 2.03234;-3.13196;-9.51195;,
 2.03234;-6.39905;-14.91466;,
 3.85158;-4.87687;-9.51195;,
 3.85158;-7.63437;-14.91466;,
 -2.16005;-9.66615;-18.41520;,
 -3.97929;-10.39187;-18.41520;,
 2.03234;-9.66615;-18.41520;,
 3.85158;-10.39187;-18.41520;,
 -2.16005;-12.93323;-18.12781;,
 -3.97929;-13.14936;-18.12781;,
 2.03234;-12.93323;-18.12781;,
 3.85158;-13.14936;-18.12781;,
 3.85158;-4.87687;-9.51195;,
 3.85158;-4.87687;-6.84531;,
 3.85158;-7.63437;-6.84531;,
 3.85158;-7.63437;-14.91466;,
 3.85158;-5.91582;-4.36034;,
 3.85158;-7.63437;-2.72282;,
 3.85158;-6.89471;1.44593;,
 3.85158;-7.63437;1.44593;,
 3.85158;-10.39187;-6.84531;,
 3.85158;-10.39187;-18.41520;,
 3.85158;-10.39187;-2.67354;,
 3.85158;-10.39187;1.49520;,
 3.85158;-13.14936;-6.84531;,
 3.85158;-13.14936;-18.12781;,
 3.85158;-13.14936;-2.67354;,
 3.85158;-13.14936;1.58209;,
 3.85158;-6.89471;1.44593;,
 2.03234;-5.52269;1.44593;,
 2.03234;-6.39905;1.44593;,
 3.85158;-7.63437;1.44593;,
 -2.16005;-5.52269;1.44593;,
 -2.16005;-6.39905;1.44593;,
 -3.97929;-6.89471;1.44593;,
 -3.97929;-7.63437;1.44593;,
 2.03234;-9.66615;1.49520;,
 3.85158;-10.39187;1.49520;,
 -2.16005;-9.66615;1.49520;,
 -3.97929;-10.39187;1.49520;,
 2.03234;-12.93323;1.58209;,
 3.85158;-13.14936;1.58209;,
 -2.16005;-12.93323;1.58209;,
 -3.97929;-13.14936;1.58209;,
 -3.97929;-6.89471;1.44593;,
 -3.97929;-5.91582;-4.36034;,
 -3.97929;-7.63437;-2.72282;,
 -3.97929;-7.63437;1.44593;,
 -3.97929;-4.87687;-6.84531;,
 -3.97929;-7.63437;-6.84531;,
 -3.97929;-4.87687;-9.44961;,
 -3.97929;-7.63437;-14.91466;,
 -3.97929;-10.39187;-2.67354;,
 -3.97929;-10.39187;1.49520;,
 -3.97929;-10.39187;-6.84531;,
 -3.97929;-10.39187;-18.41520;,
 -3.97929;-13.14936;-2.67354;,
 -3.97929;-13.14936;1.58209;,
 -3.97929;-13.14936;-6.84531;,
 -3.97929;-13.14936;-18.12781;,
 -2.16005;-5.52269;1.44593;,
 -2.16005;-4.36290;-4.36034;,
 -3.97929;-5.91582;-4.36034;,
 2.03234;-5.52269;1.44593;,
 2.03234;-4.36290;-4.36034;,
 3.85158;-5.91582;-4.36034;,
 -2.16005;-3.13196;-6.84531;,
 -3.97929;-4.87687;-6.84531;,
 2.03234;-3.13196;-6.84531;,
 3.85158;-4.87687;-6.84531;,
 -2.16005;-3.13196;-9.51195;,
 -3.97929;-4.87687;-9.44961;,
 2.03234;-3.13196;-9.51195;,
 3.85158;-4.87687;-9.51195;,
 -3.97929;-13.14936;-2.67354;,
 -2.16005;-12.93323;-2.67354;,
 -2.16005;-12.93323;1.58209;,
 2.03234;-12.93323;-2.67354;,
 2.03234;-12.93323;1.58209;,
 3.85158;-13.14936;-2.67354;,
 -3.97929;-13.14936;-6.84531;,
 -2.16005;-12.93323;-6.84531;,
 2.03234;-12.93323;-6.84531;,
 3.85158;-13.14936;-6.84531;,
 -3.97929;-13.14936;-18.12781;,
 -2.16005;-12.93323;-18.12781;,
 2.03234;-12.93323;-18.12781;,
 3.85158;-13.14936;-18.12781;,
 0.02813;0.94425;-1.75903;,
 1.64373;0.67357;-1.25522;,
 1.64373;-5.19262;-3.52289;,
 0.02813;-4.92194;-4.02671;,
 2.31292;0.02010;-0.03892;,
 2.31292;-5.84609;-2.30659;,
 1.64373;-0.63337;1.17739;,
 1.64373;-6.49957;-1.09028;,
 0.02813;-0.90404;1.68120;,
 0.02813;-6.77024;-0.58647;,
 -1.58746;-0.63337;1.17739;,
 -1.58746;-6.49957;-1.09028;,
 -2.25666;0.02010;-0.03892;,
 -2.25666;-5.84609;-2.30659;,
 -1.58746;0.67357;-1.25522;,
 -1.58746;-5.19262;-3.52289;,
 0.02813;0.94425;-1.75903;,
 0.02813;-4.92194;-4.02671;,
 0.02813;0.02010;-0.03892;,
 0.02813;0.02010;-0.03892;,
 0.02813;0.02010;-0.03892;,
 0.02813;0.02010;-0.03892;,
 0.02813;0.02010;-0.03892;,
 0.02813;0.02010;-0.03892;,
 0.02813;0.02010;-0.03892;,
 0.02813;0.02010;-0.03892;,
 0.02813;-5.84609;-2.30659;,
 0.02813;-5.84609;-2.30659;,
 0.02813;-5.84609;-2.30659;,
 0.02813;-5.84609;-2.30659;,
 0.02813;-5.84609;-2.30659;,
 0.02813;-5.84609;-2.30659;,
 0.02813;-5.84609;-2.30659;,
 0.02813;-5.84609;-2.30659;;
 
 78;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;3,2,8,9;,
 4;2,5,10,8;,
 4;5,7,11,10;,
 4;9,8,12,13;,
 4;8,10,14,12;,
 4;10,11,15,14;,
 4;16,17,18,19;,
 4;17,20,21,18;,
 4;20,22,23,21;,
 4;19,18,24,25;,
 4;18,21,26,24;,
 4;21,23,27,26;,
 4;25,24,28,29;,
 4;24,26,30,28;,
 4;26,27,31,30;,
 4;32,33,34,35;,
 4;33,36,37,34;,
 4;36,38,39,37;,
 4;35,34,40,41;,
 4;34,37,42,40;,
 4;37,39,43,42;,
 4;41,40,44,45;,
 4;40,42,46,44;,
 4;42,43,47,46;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;52,54,55,53;,
 4;51,50,56,57;,
 4;50,53,58,56;,
 4;53,55,59,58;,
 4;57,56,60,61;,
 4;56,58,62,60;,
 4;58,59,63,62;,
 4;48,64,65,66;,
 4;64,67,68,65;,
 4;67,22,69,68;,
 4;66,65,70,71;,
 4;65,68,72,70;,
 4;68,69,73,72;,
 4;71,70,74,75;,
 4;70,72,76,74;,
 4;72,73,77,76;,
 4;78,79,80,61;,
 4;79,81,82,80;,
 4;81,83,31,82;,
 4;84,85,79,78;,
 4;85,86,81,79;,
 4;86,87,83,81;,
 4;88,89,85,84;,
 4;89,90,86,85;,
 4;90,91,87,86;,
 4;92,93,94,95;,
 4;93,96,97,94;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 3;110,93,92;,
 3;111,96,93;,
 3;112,98,96;,
 3;113,100,98;,
 3;114,102,100;,
 3;115,104,102;,
 3;116,106,104;,
 3;117,108,106;,
 3;118,95,94;,
 3;119,94,97;,
 3;120,97,99;,
 3;121,99,101;,
 3;122,101,103;,
 3;123,103,105;,
 3;124,105,107;,
 3;125,107,109;;
 
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
  73;
  -0.837120;0.527633;-0.144338;,
  -0.349877;0.902907;-0.249691;,
  0.348485;0.903199;-0.250579;,
  -0.483214;0.716409;-0.503251;,
  -0.248810;0.781988;-0.571479;,
  0.247428;0.782018;-0.572037;,
  -0.200270;0.348997;-0.915474;,
  -0.099177;0.355342;-0.929460;,
  0.099177;0.355342;-0.929460;,
  0.023626;-0.095622;-0.995137;,
  0.011814;-0.091631;-0.995723;,
  -0.011814;-0.091631;-0.995723;,
  0.836127;0.528818;-0.145748;,
  0.915767;0.391939;0.088062;,
  0.903388;0.409219;0.128180;,
  0.480612;0.717076;-0.504790;,
  1.000000;0.000000;0.000000;,
  0.200270;0.348997;-0.915474;,
  -0.023626;-0.095622;-0.995137;,
  0.899892;0.428930;0.078826;,
  0.000000;0.000000;1.000000;,
  0.002171;0.007888;0.999967;,
  -0.002171;0.007888;0.999967;,
  0.003964;0.021795;0.999755;,
  -0.003964;0.021795;0.999755;,
  0.003587;0.027813;0.999607;,
  -0.003587;0.027813;0.999607;,
  -0.903388;0.409219;0.128180;,
  -0.915767;0.391939;0.088062;,
  -0.004341;0.008236;0.999957;,
  -1.000000;0.000000;0.000000;,
  -0.007928;0.022756;0.999710;,
  -0.007173;0.029040;0.999552;,
  -0.335228;0.895020;0.294213;,
  0.335228;0.895020;0.294213;,
  -0.363118;0.908023;0.208901;,
  0.363118;0.908023;0.208901;,
  0.059090;-0.998253;-0.000000;,
  -0.059090;-0.998253;0.000000;,
  -0.000000;0.880913;0.473278;,
  -0.000001;0.360564;-0.932734;,
  0.664730;0.269371;-0.696831;,
  1.000000;0.000001;-0.000001;,
  0.664730;-0.269371;0.696831;,
  -0.000001;-0.360563;0.932735;,
  -0.664728;-0.269371;0.696833;,
  -1.000000;0.000001;-0.000001;,
  -0.664729;0.269372;-0.696832;,
  0.000000;-0.880912;-0.473280;,
  0.004341;0.008236;0.999957;,
  0.007928;0.022756;0.999710;,
  0.007173;0.029040;0.999552;,
  -0.899892;0.428930;0.078826;,
  -0.327950;0.927627;0.178764;,
  0.327950;0.927627;0.178764;,
  0.117973;-0.993017;-0.000000;,
  -0.059090;-0.998253;0.000000;,
  -0.117973;-0.993017;0.000000;,
  0.000001;0.880912;0.473280;,
  -0.000000;0.880912;0.473281;,
  0.000000;0.880913;0.473278;,
  0.000001;0.880915;0.473275;,
  -0.000000;0.880915;0.473274;,
  -0.000001;0.880915;0.473275;,
  0.000000;0.880913;0.473278;,
  -0.000001;0.880912;0.473280;,
  -0.000000;-0.880913;-0.473278;,
  0.000000;-0.880913;-0.473279;,
  0.000000;-0.880912;-0.473281;,
  -0.000002;-0.880912;-0.473280;,
  0.000000;-0.880913;-0.473278;,
  0.000002;-0.880912;-0.473280;,
  -0.000000;-0.880913;-0.473279;;
  78;
  4;0,1,4,3;,
  4;1,2,5,4;,
  4;2,12,15,5;,
  4;3,4,7,6;,
  4;4,5,8,7;,
  4;5,15,17,8;,
  4;6,7,10,9;,
  4;7,8,11,10;,
  4;8,17,18,11;,
  4;12,13,16,16;,
  4;13,14,16,16;,
  4;14,19,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;20,20,21,49;,
  4;20,20,22,21;,
  4;20,20,29,22;,
  4;49,21,23,50;,
  4;21,22,24,23;,
  4;22,29,31,24;,
  4;50,23,25,51;,
  4;23,24,26,25;,
  4;24,31,32,26;,
  4;52,27,30,30;,
  4;27,28,30,30;,
  4;28,0,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;30,30,30,30;,
  4;52,53,33,27;,
  4;53,54,34,33;,
  4;54,19,14,34;,
  4;27,33,35,28;,
  4;33,34,36,35;,
  4;34,14,13,36;,
  4;28,35,1,0;,
  4;35,36,2,1;,
  4;36,13,12,2;,
  4;55,37,37,55;,
  4;37,38,56,37;,
  4;38,57,57,56;,
  4;55,37,37,55;,
  4;37,38,38,37;,
  4;38,57,57,38;,
  4;55,37,37,55;,
  4;37,56,38,37;,
  4;56,57,57,38;,
  4;40,41,41,40;,
  4;41,42,42,41;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,45,45,44;,
  4;45,46,46,45;,
  4;46,47,47,46;,
  4;47,40,40,47;,
  3;39,58,59;,
  3;39,60,58;,
  3;39,61,60;,
  3;39,62,61;,
  3;39,63,62;,
  3;39,64,63;,
  3;39,65,64;,
  3;39,59,65;,
  3;48,66,67;,
  3;48,67,68;,
  3;48,68,69;,
  3;48,69,70;,
  3;48,70,71;,
  3;48,71,68;,
  3;48,68,72;,
  3;48,72,66;;
 }
 MeshTextureCoords {
  126;
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.333330;1.000000;,
  0.666670;0.666670;,
  0.666670;1.000000;,
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
  0.937500;1.000000;;
 }
}