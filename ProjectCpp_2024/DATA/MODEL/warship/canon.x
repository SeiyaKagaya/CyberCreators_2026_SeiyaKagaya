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
 54;
 50.99519;60.93433;89.98663;,
 -50.99517;60.93433;89.98663;,
 -50.99517;-4.49607;89.98663;,
 50.99519;-4.49607;89.98663;,
 -50.99517;60.93433;89.98663;,
 -36.14688;43.17654;-42.20204;,
 -36.14688;-4.49610;-42.20204;,
 -50.99517;-4.49607;89.98663;,
 -36.14688;43.17654;-42.20204;,
 36.14687;43.17654;-42.20204;,
 36.14687;-4.49610;-42.20204;,
 -36.14688;-4.49610;-42.20204;,
 36.14687;43.17654;-42.20204;,
 50.99519;60.93433;89.98663;,
 50.99519;-4.49607;89.98663;,
 36.14687;-4.49610;-42.20204;,
 -50.99517;60.93433;89.98663;,
 50.99519;60.93433;89.98663;,
 50.99519;-4.49607;89.98663;,
 -50.99517;-4.49607;89.98663;,
 -0.00002;43.52508;-188.98532;,
 -7.87710;40.26226;-188.98532;,
 -7.87708;40.26230;31.96693;,
 -0.00000;43.52512;31.96690;,
 -11.13989;32.38537;-188.98532;,
 -11.13987;32.38540;31.96690;,
 -7.87710;24.50826;-188.98535;,
 -7.87708;24.50829;31.96692;,
 -0.00002;21.24551;-188.98532;,
 0.00000;21.24554;31.96690;,
 7.87706;24.50826;-188.98532;,
 7.87708;24.50829;31.96693;,
 11.13985;32.38537;-188.98532;,
 11.13987;32.38540;31.96690;,
 7.87706;40.26226;-188.98532;,
 7.87708;40.26230;31.96693;,
 -0.00002;43.52508;-188.98532;,
 -0.00000;43.52512;31.96690;,
 -0.00002;32.38537;-188.98532;,
 -0.00002;32.38537;-188.98532;,
 -0.00002;32.38537;-188.98532;,
 -0.00002;32.38537;-188.98532;,
 -0.00002;32.38537;-188.98532;,
 -0.00002;32.38537;-188.98532;,
 -0.00002;32.38537;-188.98532;,
 -0.00002;32.38537;-188.98532;,
 -0.00000;32.38540;31.96690;,
 -0.00000;32.38540;31.96690;,
 -0.00000;32.38540;31.96690;,
 -0.00000;32.38540;31.96690;,
 -0.00000;32.38540;31.96690;,
 -0.00000;32.38540;31.96690;,
 -0.00000;32.38540;31.96690;,
 -0.00000;32.38540;31.96690;;
 
 30;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;21,24,25,22;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 3;38,21,20;,
 3;39,24,21;,
 3;40,26,24;,
 3;41,28,26;,
 3;42,30,28;,
 3;43,32,30;,
 3;44,34,32;,
 3;45,36,34;,
 3;46,23,22;,
 3;47,22,25;,
 3;48,25,27;,
 3;49,27,29;,
 3;50,29,31;,
 3;51,31,33;,
 3;52,33,35;,
 3;53,35,37;;
 
 MeshMaterialList {
  2;
  30;
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
   0.432800;0.432800;0.432800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.476800;0.000000;0.028000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  28;
  0.000000;0.000000;1.000000;,
  -0.993750;0.000000;-0.111625;,
  0.000000;0.000000;-1.000000;,
  0.993750;0.000000;-0.111625;,
  0.000000;0.991097;-0.133141;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;1.000000;-0.000000;,
  -0.707105;0.707109;-0.000000;,
  -1.000000;0.000005;0.000000;,
  -0.707106;-0.707108;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.707106;-0.707108;0.000000;,
  1.000000;0.000005;-0.000000;,
  0.707105;0.707109;-0.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000002;-1.000000;,
  0.000002;0.000002;-1.000000;,
  0.000002;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000002;-0.000002;1.000000;,
  0.000000;-0.000001;1.000000;,
  0.000001;0.000001;1.000000;,
  -0.000001;-0.000000;1.000000;,
  -0.000002;0.000002;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000002;-0.000002;1.000000;;
  30;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,7,7,14;,
  3;6,16,16;,
  3;6,17,16;,
  3;6,18,17;,
  3;6,19,18;,
  3;6,16,19;,
  3;6,16,16;,
  3;6,16,16;,
  3;6,16,16;,
  3;15,20,21;,
  3;15,21,22;,
  3;15,22,23;,
  3;15,23,24;,
  3;15,24,25;,
  3;15,25,26;,
  3;15,26,27;,
  3;15,27,20;;
 }
 MeshTextureCoords {
  54;
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