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
 237;
 12.00000;-3.42400;-7.08000;,
 12.06000;5.30936;-7.28048;,
 19.71464;5.28944;-12.45080;,
 19.65448;-3.44392;-12.25032;,
 30.33456;5.20664;-10.51976;,
 30.27456;-3.52664;-10.26752;,
 39.47216;5.15528;-6.60040;,
 39.41216;-3.57800;-6.39992;,
 48.60944;5.10392;-6.10344;,
 48.54936;-3.62944;-5.90288;,
 57.74664;5.05256;-5.60640;,
 57.68664;-3.68072;-5.40592;,
 12.06000;5.30936;-7.28048;,
 11.58680;5.51280;1.44016;,
 20.72424;5.46144;0.14104;,
 19.71464;5.28944;-12.45080;,
 29.86128;5.41008;0.44984;,
 30.33456;5.20664;-10.51976;,
 38.99896;5.35872;4.04896;,
 39.47216;5.15528;-6.60040;,
 48.13624;5.30744;2.61728;,
 48.60944;5.10392;-6.10344;,
 57.27344;5.25608;3.11424;,
 57.74664;5.05256;-5.60640;,
 11.58680;5.51280;1.44016;,
 11.52672;-3.22048;1.64064;,
 20.66424;-3.27192;0.34160;,
 20.72424;5.46144;0.14104;,
 29.80128;-3.32328;0.70200;,
 29.86128;5.41008;0.44984;,
 38.93888;-3.37464;4.24944;,
 38.99896;5.35872;4.04896;,
 48.07624;-3.42592;2.81776;,
 48.13624;5.30744;2.61728;,
 57.21352;-3.47736;3.31472;,
 57.27344;5.25608;3.11424;,
 11.52672;-3.22048;1.64064;,
 12.00000;-3.42400;-7.08000;,
 19.65448;-3.44392;-12.25032;,
 20.66424;-3.27192;0.34160;,
 30.27456;-3.52664;-10.26752;,
 29.80128;-3.32328;0.70200;,
 39.41216;-3.57800;-6.39992;,
 38.93888;-3.37464;4.24944;,
 48.54936;-3.62944;-5.90288;,
 48.07624;-3.42592;2.81776;,
 57.68664;-3.68072;-5.40592;,
 57.21352;-3.47736;3.31472;,
 12.06000;5.30936;-7.28048;,
 12.00000;-3.42400;-7.08000;,
 57.68664;-3.68072;-5.40592;,
 57.74664;5.05256;-5.60640;,
 25.09592;-5.16024;5.65392;,
 26.75632;6.31192;5.62192;,
 56.82288;5.28640;3.46624;,
 54.95016;-3.38760;3.49824;,
 26.75632;6.31192;5.62192;,
 27.45840;6.33248;18.95160;,
 57.52520;5.30696;10.13168;,
 56.82288;5.28640;3.46624;,
 27.45840;6.33248;18.95160;,
 25.79824;-5.13976;18.98360;,
 55.65224;-3.36696;10.16368;,
 57.52520;5.30696;10.13168;,
 25.79824;-5.13976;18.98360;,
 25.09592;-5.16024;5.65392;,
 54.95016;-3.38760;3.49824;,
 55.65224;-3.36696;10.16368;,
 26.75632;6.31192;5.62192;,
 25.09592;-5.16024;5.65392;,
 54.95016;-3.38760;3.49824;,
 56.82288;5.28640;3.46624;,
 -8.75720;-4.64968;26.09736;,
 -8.65632;2.92616;25.82856;,
 26.68456;6.09264;5.13448;,
 26.85976;-3.49536;5.66480;,
 -8.65632;2.92616;25.82856;,
 -6.37632;1.52936;29.20704;,
 27.50472;5.93664;18.70120;,
 26.68456;6.09264;5.13448;,
 -6.37632;1.52936;29.20704;,
 -7.88352;-2.44104;31.07240;,
 25.66384;-5.42552;19.19328;,
 27.50472;5.93664;18.70120;,
 -7.88352;-2.44104;31.07240;,
 -8.75720;-4.64968;26.09736;,
 26.85976;-3.49536;5.66480;,
 25.66384;-5.42552;19.19328;,
 -8.65632;2.92616;25.82856;,
 -8.75720;-4.64968;26.09736;,
 26.85976;-3.49536;5.66480;,
 26.68456;6.09264;5.13448;,
 44.62104;5.44784;2.22512;,
 44.54728;3.56776;2.22512;,
 28.09576;4.70160;-1.18096;,
 28.16952;6.58040;-1.18096;,
 42.90040;3.52640;9.80952;,
 42.97416;5.40656;9.80952;,
 20.08264;6.93936;13.31840;,
 20.00896;5.06048;13.31840;,
 11.04184;4.83584;11.65976;,
 11.11552;6.71464;11.65976;,
 2.94312;3.37400;-2.09912;,
 11.04184;4.83584;-0.23080;,
 1.00608;3.17616;9.47616;,
 1.07648;4.97216;9.47616;,
 3.01688;5.25280;-2.09912;,
 18.69520;6.90464;-11.49768;,
 18.62176;5.02568;-11.49768;,
 13.78288;4.74520;-8.50424;,
 13.85040;6.46600;-8.50424;,
 8.90712;4.15656;-5.40240;,
 8.97664;5.92544;-5.40240;,
 41.98160;7.30680;3.84336;,
 40.84392;7.27840;8.74408;,
 27.52592;8.48960;0.83464;,
 20.09728;8.86488;12.00984;,
 12.17840;8.66648;10.45544;,
 12.17840;8.66648;-0.29336;,
 3.53200;7.19096;8.44408;,
 5.00120;7.22784;-0.64896;,
 14.85616;8.73360;-5.99000;,
 18.65536;8.82880;-8.55560;,
 10.64232;8.06640;-3.48824;,
 44.27408;-3.40184;2.22512;,
 27.77496;-3.48336;-1.18096;,
 44.34768;-1.52296;2.22512;,
 27.70120;-5.36360;-1.18096;,
 42.70088;-1.56424;9.80952;,
 19.57040;-6.12896;13.31840;,
 42.62720;-3.44312;9.80952;,
 19.64408;-4.24872;13.31840;,
 10.67704;-4.47352;11.65976;,
 10.60328;-6.35360;11.65976;,
 2.67704;-3.41512;-2.09912;,
 10.67688;-4.47336;-0.23080;,
 0.75160;-3.31416;9.47616;,
 0.68112;-5.11152;9.47616;,
 2.60344;-5.29416;-2.09912;,
 18.18304;-6.16360;-11.49768;,
 18.25672;-4.28352;-11.49768;,
 13.43048;-4.24520;-8.50424;,
 13.36304;-5.96616;-8.50424;,
 8.59136;-3.90016;-5.40240;,
 8.52208;-5.66912;-5.40240;,
 41.48368;-5.39712;3.84336;,
 40.34592;-5.42552;8.74408;,
 26.90664;-7.30752;0.83464;,
 19.43392;-8.05744;12.00984;,
 11.51504;-8.25592;10.45544;,
 11.51504;-8.25592;-0.29328;,
 2.96760;-7.21024;8.44408;,
 4.43672;-7.17328;-0.64896;,
 14.19280;-8.18888;-5.99000;,
 17.99192;-8.09360;-8.55560;,
 10.02320;-7.73056;-3.48824;,
 56.02064;4.14656;-5.41560;,
 58.36312;4.26944;-5.41560;,
 58.04440;-1.49872;-5.41560;,
 55.82496;-1.55424;-5.41560;,
 58.36312;4.26944;-5.41560;,
 58.36312;4.26944;2.49088;,
 58.04440;-1.49872;2.49088;,
 58.04440;-1.49872;-5.41560;,
 58.36312;4.26944;2.49088;,
 56.02064;4.14656;2.49088;,
 55.82496;-1.55424;2.49088;,
 58.04440;-1.49872;2.49088;,
 56.02064;4.14656;2.49088;,
 56.02064;4.14656;-5.41560;,
 55.82496;-1.55424;-5.41560;,
 55.82496;-1.55424;2.49088;,
 58.36312;4.26944;-5.41560;,
 56.02064;4.14656;-5.41560;,
 55.82496;-1.55424;-5.41560;,
 58.04440;-1.49872;-5.41560;,
 -9.37048;-4.35952;26.88576;,
 -9.12984;3.11176;26.86776;,
 -8.82392;1.82968;25.55088;,
 -9.00184;-2.71136;25.55088;,
 -2.93552;3.24704;16.49544;,
 -3.18864;-3.20856;16.49544;,
 -8.24432;-2.88240;23.74648;,
 -8.05040;2.06128;23.74648;,
 6.34832;4.90384;19.37912;,
 -1.98216;3.82880;16.49544;,
 -2.27904;-3.74360;16.49544;,
 6.03912;-5.03952;19.40696;,
 3.24568;3.45272;12.26120;,
 2.99256;-3.00296;12.26120;,
 4.19904;4.03440;12.26120;,
 3.90208;-3.53792;12.26120;,
 9.61112;-5.61336;17.98432;,
 9.99112;6.13728;17.95512;,
 8.86032;3.68896;8.35512;,
 8.60720;-2.76680;8.35512;,
 9.81496;4.27064;8.35512;,
 9.51808;-3.30184;8.35512;,
 19.94672;-5.35424;13.35728;,
 20.32680;6.39640;13.32808;,
 0.06952;1.25216;8.29680;,
 -0.04072;-1.56184;8.29680;,
 6.80624;-1.39016;8.29680;,
 6.91664;1.42384;8.29680;,
 -0.04072;-1.56184;-7.33048;,
 0.06952;1.25216;-7.33048;,
 6.91664;1.42384;-7.33048;,
 6.80624;-1.39016;-7.33048;,
 10.93808;1.52464;-4.86480;,
 10.93808;1.52464;5.83256;,
 11.04840;4.33728;5.83256;,
 11.04840;4.33728;-4.86480;,
 6.69600;-4.20304;8.29680;,
 10.71752;-4.10224;5.83256;,
 10.82776;-1.28936;5.83256;,
 10.82776;-1.28936;-4.86480;,
 10.71752;-4.10224;-4.86480;,
 11.00336;-1.65528;5.96728;,
 14.00144;-1.58016;5.96728;,
 14.14080;1.97512;5.96728;,
 11.14264;1.89992;5.96728;,
 11.14264;1.89992;-4.99952;,
 14.14080;1.97512;-4.99952;,
 14.00144;-1.58016;-4.99952;,
 11.00336;-1.65528;-4.99952;,
 7.14080;-1.75216;4.84352;,
 7.28000;1.80320;4.84352;,
 7.14080;-1.75216;-3.87576;,
 7.28000;1.80320;-3.87576;,
 10.90640;-4.12592;5.96728;,
 10.90640;-4.12592;-4.99952;,
 13.90464;-4.05072;5.96728;,
 13.90464;-4.05072;-4.99952;,
 11.23944;4.37056;-4.99952;,
 11.23944;4.37056;5.96728;,
 14.23768;4.44568;-4.99952;,
 14.23768;4.44568;5.96728;;
 
 233;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;12,13,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;24,25,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 4;31,30,32,33;,
 4;33,32,34,35;,
 4;36,37,38,39;,
 4;39,38,40,41;,
 4;41,40,42,43;,
 4;43,42,44,45;,
 4;45,44,46,47;,
 4;36,13,48,49;,
 4;50,51,22,47;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;64,57,68,69;,
 4;70,71,58,67;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;84,77,88,89;,
 4;90,91,78,87;,
 3;92,93,94;,
 3;92,94,95;,
 3;96,97,98;,
 3;96,98,99;,
 3;98,100,99;,
 3;98,101,100;,
 3;102,103,100;,
 3;102,100,104;,
 3;100,101,104;,
 3;101,105,104;,
 3;106,102,104;,
 3;106,104,105;,
 3;94,107,95;,
 3;94,108,107;,
 3;103,108,94;,
 3;103,109,108;,
 3;110,107,108;,
 3;110,108,109;,
 3;106,111,102;,
 3;106,112,111;,
 3;103,111,109;,
 3;102,111,103;,
 3;110,109,112;,
 3;111,112,109;,
 3;113,114,97;,
 3;113,97,92;,
 3;92,115,113;,
 3;92,95,115;,
 3;113,115,114;,
 3;98,114,116;,
 3;97,114,98;,
 3;114,115,116;,
 3;101,116,117;,
 3;98,116,101;,
 3;115,117,116;,
 3;115,118,117;,
 3;105,117,119;,
 3;101,117,105;,
 3;117,118,119;,
 3;106,119,120;,
 3;106,105,119;,
 3;118,120,119;,
 3;115,121,118;,
 3;95,122,115;,
 3;95,107,122;,
 3;121,122,107;,
 3;110,121,107;,
 3;115,122,121;,
 3;112,120,123;,
 3;106,120,112;,
 3;118,123,120;,
 3;110,123,121;,
 3;110,112,123;,
 3;118,121,123;,
 3;124,125,126;,
 3;124,127,125;,
 3;128,129,130;,
 3;128,131,129;,
 3;129,131,132;,
 3;129,132,133;,
 3;134,132,135;,
 3;134,136,132;,
 3;132,136,133;,
 3;133,136,137;,
 3;138,136,134;,
 3;138,137,136;,
 3;125,127,139;,
 3;125,139,140;,
 3;135,125,140;,
 3;135,140,141;,
 3;142,140,139;,
 3;142,141,140;,
 3;138,134,143;,
 3;138,143,144;,
 3;135,141,143;,
 3;134,135,143;,
 3;142,144,141;,
 3;143,141,144;,
 3;145,124,130;,
 3;145,130,146;,
 3;124,147,127;,
 3;124,145,147;,
 3;145,146,147;,
 3;129,146,130;,
 3;129,148,146;,
 3;146,148,147;,
 3;129,133,148;,
 3;133,149,148;,
 3;147,148,149;,
 3;147,149,150;,
 3;133,137,149;,
 3;137,151,149;,
 3;149,151,150;,
 3;138,151,137;,
 3;138,152,151;,
 3;150,151,152;,
 3;147,150,153;,
 3;127,154,139;,
 3;127,147,154;,
 3;142,139,153;,
 3;153,139,154;,
 3;147,153,154;,
 3;138,144,152;,
 3;144,155,152;,
 3;150,152,155;,
 3;142,155,144;,
 3;142,153,155;,
 3;150,155,153;,
 4;156,157,158,159;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;168,161,172,173;,
 4;174,175,162,171;,
 3;176,177,178;,
 3;176,178,179;,
 3;180,181,182;,
 3;180,182,183;,
 3;176,179,182;,
 3;178,183,182;,
 3;178,182,179;,
 3;176,182,181;,
 3;177,183,178;,
 3;177,180,183;,
 3;184,185,177;,
 3;186,187,176;,
 3;176,181,186;,
 3;177,185,180;,
 3;180,188,181;,
 3;181,188,189;,
 3;185,190,188;,
 3;186,189,191;,
 3;187,191,192;,
 3;184,193,190;,
 3;184,190,185;,
 3;180,185,188;,
 3;181,189,186;,
 3;186,191,187;,
 3;188,194,195;,
 3;188,195,189;,
 3;190,196,194;,
 3;191,195,197;,
 3;189,195,191;,
 3;192,197,198;,
 3;193,199,196;,
 3;190,193,196;,
 3;188,190,194;,
 3;191,197,192;,
 3;200,201,202;,
 3;200,202,203;,
 3;204,205,206;,
 3;204,206,207;,
 3;205,204,201;,
 3;205,201,200;,
 3;203,202,207;,
 3;203,207,206;,
 3;208,209,203;,
 3;208,203,206;,
 3;210,209,208;,
 3;210,208,211;,
 3;202,212,213;,
 3;214,215,207;,
 3;214,207,202;,
 3;214,213,216;,
 3;214,216,215;,
 3;217,218,219;,
 3;217,219,220;,
 3;221,222,223;,
 3;221,223,224;,
 3;217,220,225;,
 3;220,226,225;,
 3;227,224,217;,
 3;227,217,225;,
 3;221,224,228;,
 3;224,227,228;,
 3;226,220,221;,
 3;226,221,228;,
 3;226,228,227;,
 3;226,227,225;,
 3;229,217,224;,
 3;229,224,230;,
 3;217,231,218;,
 3;217,229,231;,
 3;232,223,218;,
 3;232,218,231;,
 3;223,230,224;,
 3;223,232,230;,
 3;230,232,231;,
 3;230,231,229;,
 3;233,221,220;,
 3;233,220,234;,
 3;221,235,222;,
 3;221,233,235;,
 3;236,219,222;,
 3;236,222,235;,
 3;219,234,220;,
 3;219,236,234;,
 3;234,236,235;,
 3;234,235,233;;
 
 MeshMaterialList {
  52;
  233;
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  25,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  5,
  5,
  5,
  5,
  5,
  5,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16;;
  Material {
   0.126000;0.126000;0.126000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.722000;0.722000;0.722000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.377000;0.392000;0.392000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.439000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.502000;0.502000;1.000000;1.000000;;
   5.000000;
   0.502000;0.502000;0.502000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.126000;0.126000;0.126000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.658000;0.549000;0.173000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.188000;0.188000;0.188000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.126000;0.126000;0.126000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.722000;0.722000;0.722000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.439000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.320000;0.126000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.502000;0.502000;1.000000;1.000000;;
   5.000000;
   0.502000;0.502000;0.502000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.251000;0.251000;0.251000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.658000;0.549000;0.173000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.188000;0.188000;0.188000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.126000;0.126000;0.126000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.722000;0.722000;0.722000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.126000;0.126000;0.126000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.188000;0.188000;0.188000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.502000;0.502000;0.502000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.126000;0.126000;0.126000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.722000;0.722000;0.722000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.157000;0.534000;0.000000;1.000000;;
   110.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.439000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.621000;0.621000;0.621000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.658000;0.549000;0.173000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.188000;0.188000;0.188000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.126000;0.126000;0.126000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.722000;0.722000;0.722000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.377000;0.392000;0.392000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.439000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.502000;0.502000;1.000000;1.000000;;
   5.000000;
   0.502000;0.502000;0.502000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.439000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.251000;0.251000;0.251000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.658000;0.549000;0.173000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.398000;0.398000;0.398000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.398000;0.398000;0.398000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.558000;0.558000;0.558000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.398000;0.398000;0.398000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.420000;0.449000;0.342000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.562000;0.562000;0.562000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.502000;0.502000;0.251000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.398000;0.398000;0.398000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  199;
  -0.870035;-0.005334;-0.492961;,
  -0.204581;-0.022630;-0.978588;,
  0.288088;-0.026788;-0.957229;,
  0.226372;-0.025292;-0.973712;,
  0.054167;-0.023293;-0.998260;,
  0.054167;-0.023293;-0.998260;,
  -0.001981;0.999833;-0.018176;,
  0.003177;0.999846;-0.017280;,
  0.010727;0.999793;-0.017315;,
  0.008937;0.999768;-0.019608;,
  0.005810;0.999742;-0.021964;,
  0.006868;0.999713;-0.022958;,
  0.140842;0.021758;0.989793;,
  0.052410;0.024045;0.998336;,
  -0.203044;0.026762;0.978804;,
  -0.108279;0.024983;0.993807;,
  0.050636;0.022572;0.998462;,
  -0.054163;0.023287;0.998261;,
  -0.071793;0.009690;-0.997373;,
  0.033369;0.999431;-0.004955;,
  0.282249;-0.047685;0.958155;,
  -0.498845;-0.040549;-0.865742;,
  -0.010325;0.984950;0.172530;,
  0.323433;0.143293;0.935338;,
  0.214553;0.417042;-0.883200;,
  0.202207;-0.007933;-0.979311;,
  0.492779;-0.019311;-0.869940;,
  0.491797;0.475048;-0.729702;,
  0.151123;-0.005928;0.988497;,
  0.164512;0.324898;0.931331;,
  0.015729;0.263039;0.964657;,
  -0.015684;0.000615;0.999877;,
  -0.192699;0.007557;0.981229;,
  -0.212380;0.309772;0.926788;,
  0.167434;-0.985591;0.023987;,
  0.114843;-0.992985;0.028135;,
  0.161018;-0.986900;0.010077;,
  -0.266111;0.440599;0.857355;,
  -0.788089;0.394400;-0.472614;,
  0.719301;0.236729;-0.653119;,
  0.735794;-0.028758;-0.676594;,
  0.120356;-0.991433;0.050736;,
  -0.513354;0.426169;-0.744881;,
  -0.503921;0.019798;-0.863523;,
  -0.498381;0.430601;-0.752462;,
  0.410230;0.908688;-0.077444;,
  0.245809;0.884029;0.397582;,
  0.126803;0.972034;-0.197662;,
  -0.023101;0.837851;0.545410;,
  -0.165197;0.895946;0.412300;,
  -0.123613;0.991834;-0.031376;,
  -0.437419;0.892849;0.107167;,
  -0.378234;0.886412;-0.266858;,
  -0.242836;0.929127;-0.278842;,
  0.196253;0.895455;-0.399556;,
  -0.330692;0.874782;-0.354117;,
  0.232963;-0.425343;-0.874535;,
  0.492780;-0.019321;-0.869940;,
  0.202208;-0.007921;-0.979311;,
  0.500308;-0.492357;-0.712233;,
  0.151124;-0.005924;0.988497;,
  0.027990;-0.263641;0.964215;,
  0.179704;-0.333728;0.925382;,
  -0.015685;0.000615;0.999877;,
  -0.192698;0.007557;0.981229;,
  -0.198841;-0.298283;0.933536;,
  0.120499;0.992413;0.024405;,
  0.066650;0.997365;0.028634;,
  0.113784;0.993452;0.010262;,
  -0.248150;-0.429664;0.868222;,
  -0.797723;-0.358103;-0.485180;,
  0.716628;-0.278152;-0.639590;,
  0.735785;-0.028835;-0.676601;,
  0.071905;0.996086;0.051401;,
  -0.505001;-0.405467;-0.761952;,
  -0.503921;0.019736;-0.863524;,
  -0.488995;-0.410856;-0.769468;,
  0.429555;-0.899652;-0.078160;,
  0.278205;-0.878620;0.388109;,
  0.170253;-0.966682;-0.191153;,
  0.017231;-0.836539;0.547637;,
  -0.123940;-0.898069;0.422031;,
  -0.076357;-0.996559;-0.032235;,
  -0.418917;-0.901498;0.108672;,
  -0.351847;-0.893625;-0.278637;,
  -0.205855;-0.934240;-0.291238;,
  0.221630;-0.893886;-0.389676;,
  -0.298864;-0.880198;-0.368688;,
  0.000000;0.000000;-1.000000;,
  0.998477;-0.055172;-0.000000;,
  0.000000;0.000000;1.000000;,
  -0.883453;-0.285108;-0.371786;,
  -0.836126;0.413135;-0.360850;,
  -0.943139;0.061015;-0.326751;,
  -0.943464;-0.008468;-0.331367;,
  -0.703273;0.387131;-0.596269;,
  -0.650459;-0.344930;-0.676703;,
  -0.876004;-0.075549;-0.476350;,
  -0.869891;0.194718;-0.453182;,
  -0.182855;0.982249;-0.041845;,
  -0.330180;0.884342;-0.330031;,
  -0.307192;-0.863397;-0.400223;,
  -0.136435;-0.979147;-0.150521;,
  -0.543463;0.333328;-0.770416;,
  -0.502269;-0.428575;-0.751032;,
  -0.327574;0.875930;-0.354178;,
  -0.282416;-0.863464;-0.417938;,
  -0.137193;-0.969854;-0.201397;,
  -0.203058;0.970377;-0.130904;,
  -0.506814;0.505971;-0.697949;,
  -0.523878;-0.354549;-0.774498;,
  -0.243473;0.913423;-0.326159;,
  -0.207081;-0.904505;-0.372811;,
  -0.079537;-0.969469;-0.231956;,
  -0.108556;0.976186;-0.187819;,
  0.000000;0.000000;1.000000;,
  0.180266;-0.007065;0.983593;,
  0.522739;-0.020487;0.852247;,
  0.025058;-0.999686;-0.000000;,
  0.999232;-0.039193;-0.000000;,
  0.025058;-0.999686;-0.000000;,
  0.999232;-0.039193;-0.000000;,
  0.872010;-0.034175;0.488293;,
  -0.025057;0.999686;0.000000;,
  0.999233;-0.039161;-0.000000;,
  -0.056279;0.002205;0.998413;,
  -0.141211;0.005530;0.989964;,
  -0.056278;0.002205;-0.998413;,
  -0.141211;0.005530;-0.989964;,
  -0.279587;0.010950;0.960058;,
  -0.279584;0.010946;0.960059;,
  0.025074;-0.999686;-0.000000;,
  -0.279588;0.010950;-0.960058;,
  -0.999231;0.039215;0.000000;,
  0.999233;-0.039151;-0.000000;,
  -0.999233;0.039150;0.000000;,
  0.999232;-0.039184;-0.000000;,
  0.001977;-0.999833;0.018180;,
  -0.003220;-0.999846;0.017280;,
  -0.010717;-0.999793;0.017312;,
  -0.008887;-0.999768;0.019605;,
  -0.005813;-0.999742;0.021958;,
  -0.006867;-0.999713;0.022949;,
  -0.998508;0.005618;-0.054317;,
  0.998509;-0.005608;0.054307;,
  0.058932;-0.998259;-0.002347;,
  -0.988338;0.143179;0.051845;,
  0.972321;-0.210315;-0.101783;,
  0.003854;-0.991424;0.130625;,
  -0.930316;0.205627;0.303694;,
  0.997446;-0.071383;0.002299;,
  0.169333;-0.985546;0.005039;,
  -0.213924;0.008387;0.976814;,
  -0.816866;0.032069;-0.575936;,
  -0.985655;0.038666;-0.164286;,
  -0.902304;0.407257;-0.141382;,
  0.036030;-0.999323;0.007402;,
  -0.009151;-0.999694;-0.023000;,
  -0.465442;0.562384;-0.683439;,
  -0.526856;0.020632;-0.849704;,
  -0.534602;0.020988;-0.844843;,
  0.161427;-0.984889;0.062730;,
  0.618438;0.772673;0.143212;,
  0.626131;0.767022;0.140133;,
  0.122467;0.992459;0.005137;,
  -0.213920;0.008391;0.976815;,
  -0.985655;0.038629;-0.164295;,
  -0.816864;0.031996;-0.575942;,
  -0.919037;-0.365794;-0.146854;,
  -0.059058;0.997991;-0.022916;,
  -0.013789;0.999876;0.007571;,
  -0.526858;0.020647;-0.849702;,
  -0.450704;-0.550682;-0.702578;,
  -0.534605;0.020945;-0.844843;,
  0.114293;0.991397;0.063793;,
  0.626001;-0.768613;0.131747;,
  0.619167;-0.773621;0.134697;,
  -0.999411;0.034306;0.000000;,
  -0.052385;0.998627;0.000000;,
  0.025008;-0.999687;-0.000000;,
  -0.122568;0.992333;-0.015863;,
  -0.107419;-0.985448;-0.131730;,
  -0.999234;0.039146;0.000000;,
  0.999231;-0.039202;-0.000000;,
  0.025058;-0.999686;-0.000000;,
  0.999233;-0.039161;-0.000000;,
  0.025074;-0.999686;-0.000000;,
  -0.279590;0.010947;-0.960057;,
  -0.025032;0.999687;0.000000;,
  -0.025032;0.999687;0.000000;,
  -0.999234;0.039122;0.000000;,
  -0.999234;0.039122;0.000000;,
  0.999233;-0.039151;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.025074;-0.999686;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.999232;-0.039183;-0.000000;,
  -0.025047;0.999686;0.000000;,
  -0.025047;0.999686;0.000000;;
  233;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;4,4,5,5;,
  4;6,6,7,7;,
  4;7,7,8,8;,
  4;8,8,9,9;,
  4;9,9,10,10;,
  4;10,10,11,11;,
  4;12,12,13,13;,
  4;13,13,14,14;,
  4;14,14,15,15;,
  4;15,15,16,16;,
  4;16,16,17,17;,
  4;137,137,138,138;,
  4;138,138,139,139;,
  4;139,139,140,140;,
  4;140,140,141,141;,
  4;141,141,142,142;,
  4;143,143,0,0;,
  4;144,144,144,144;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;145,145,145,145;,
  4;146,146,146,146;,
  4;147,147,147,147;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;148,148,148,148;,
  4;149,149,149,149;,
  4;150,150,150,150;,
  3;24,25,26;,
  3;24,26,27;,
  3;28,29,30;,
  3;28,30,31;,
  3;30,32,31;,
  3;30,33,32;,
  3;34,35,151;,
  3;34,151,36;,
  3;32,33,152;,
  3;33,37,152;,
  3;38,153,154;,
  3;38,154,155;,
  3;26,39,27;,
  3;26,40,39;,
  3;35,156,157;,
  3;35,41,156;,
  3;42,158,159;,
  3;42,159,160;,
  3;38,43,153;,
  3;38,44,43;,
  3;35,161,41;,
  3;34,161,35;,
  3;42,160,44;,
  3;43,44,160;,
  3;45,46,162;,
  3;45,162,163;,
  3;24,47,45;,
  3;24,27,47;,
  3;45,47,46;,
  3;30,46,48;,
  3;29,46,30;,
  3;46,47,48;,
  3;33,48,49;,
  3;30,48,33;,
  3;47,49,48;,
  3;47,50,49;,
  3;37,49,51;,
  3;33,49,37;,
  3;49,50,51;,
  3;38,51,52;,
  3;38,155,51;,
  3;50,52,51;,
  3;47,53,50;,
  3;27,54,47;,
  3;27,39,54;,
  3;53,54,158;,
  3;42,53,158;,
  3;47,54,53;,
  3;44,52,55;,
  3;38,52,44;,
  3;50,55,52;,
  3;42,55,53;,
  3;42,44,55;,
  3;50,53,55;,
  3;56,57,58;,
  3;56,59,57;,
  3;60,61,62;,
  3;60,63,61;,
  3;61,63,64;,
  3;61,64,65;,
  3;66,164,67;,
  3;66,68,164;,
  3;64,165,65;,
  3;65,165,69;,
  3;70,166,167;,
  3;70,168,166;,
  3;57,59,71;,
  3;57,71,72;,
  3;67,169,170;,
  3;67,170,73;,
  3;74,171,172;,
  3;74,173,171;,
  3;70,167,75;,
  3;70,75,76;,
  3;67,73,174;,
  3;66,67,174;,
  3;74,76,173;,
  3;75,173,76;,
  3;77,175,176;,
  3;77,176,78;,
  3;56,79,59;,
  3;56,77,79;,
  3;77,78,79;,
  3;61,78,62;,
  3;61,80,78;,
  3;78,80,79;,
  3;61,65,80;,
  3;65,81,80;,
  3;79,80,81;,
  3;79,81,82;,
  3;65,69,81;,
  3;69,83,81;,
  3;81,83,82;,
  3;70,83,168;,
  3;70,84,83;,
  3;82,83,84;,
  3;79,82,85;,
  3;59,86,71;,
  3;59,79,86;,
  3;74,172,85;,
  3;85,172,86;,
  3;79,85,86;,
  3;70,76,84;,
  3;76,87,84;,
  3;82,84,87;,
  3;74,87,76;,
  3;74,85,87;,
  3;82,87,85;,
  4;88,88,88,88;,
  4;89,89,89,89;,
  4;90,90,90,90;,
  4;177,177,177,177;,
  4;178,178,178,178;,
  4;179,179,179,179;,
  3;91,92,93;,
  3;91,93,94;,
  3;95,96,97;,
  3;95,97,98;,
  3;91,94,97;,
  3;93,98,97;,
  3;93,97,94;,
  3;91,97,96;,
  3;92,98,93;,
  3;92,95,98;,
  3;99,100,180;,
  3;101,102,181;,
  3;91,96,101;,
  3;92,100,95;,
  3;95,103,96;,
  3;96,103,104;,
  3;100,105,103;,
  3;101,104,106;,
  3;102,106,107;,
  3;99,108,105;,
  3;99,105,100;,
  3;95,100,103;,
  3;96,104,101;,
  3;101,106,102;,
  3;103,109,110;,
  3;103,110,104;,
  3;105,111,109;,
  3;106,110,112;,
  3;104,110,106;,
  3;107,112,113;,
  3;108,114,111;,
  3;105,108,111;,
  3;103,105,109;,
  3;106,112,107;,
  3;90,115,116;,
  3;90,116,115;,
  3;88,88,88;,
  3;88,88,88;,
  3;182,182,182;,
  3;182,182,182;,
  3;183,183,183;,
  3;183,183,183;,
  3;120,118,120;,
  3;120,120,184;,
  3;119,121,119;,
  3;119,119,121;,
  3;116,117,122;,
  3;123,123,123;,
  3;123,123,123;,
  3;124,122,124;,
  3;124,124,185;,
  3;125,90,90;,
  3;125,90,126;,
  3;127,88,88;,
  3;127,88,128;,
  3;125,126,129;,
  3;126,130,129;,
  3;131,186,131;,
  3;131,131,131;,
  3;127,128,132;,
  3;128,187,132;,
  3;188,189,188;,
  3;188,188,188;,
  3;190,191,190;,
  3;190,190,191;,
  3;133,133,133;,
  3;133,133,133;,
  3;125,90,90;,
  3;125,90,90;,
  3;134,192,134;,
  3;134,134,192;,
  3;88,88,128;,
  3;88,193,88;,
  3;194,194,194;,
  3;194,194,194;,
  3;135,135,135;,
  3;135,135,135;,
  3;127,88,88;,
  3;127,195,88;,
  3;136,196,136;,
  3;136,136,196;,
  3;90,90,126;,
  3;90,90,90;,
  3;197,198,197;,
  3;197,197,198;;
 }
 MeshTextureCoords {
  237;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.000000;0.200000;,
  1.000000;0.400000;,
  0.000000;0.400000;,
  1.000000;0.600000;,
  0.000000;0.600000;,
  1.000000;0.800000;,
  0.000000;0.800000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.000000;0.200000;,
  1.000000;0.400000;,
  0.000000;0.400000;,
  1.000000;0.600000;,
  0.000000;0.600000;,
  1.000000;0.800000;,
  0.000000;0.800000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.000000;0.200000;,
  1.000000;0.400000;,
  0.000000;0.400000;,
  1.000000;0.600000;,
  0.000000;0.600000;,
  1.000000;0.800000;,
  0.000000;0.800000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.000000;0.200000;,
  1.000000;0.400000;,
  0.000000;0.400000;,
  1.000000;0.600000;,
  0.000000;0.600000;,
  1.000000;0.800000;,
  0.000000;0.800000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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