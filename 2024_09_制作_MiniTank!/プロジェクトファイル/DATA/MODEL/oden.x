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
 5.50580;200.17149;-97.66850;,
 99.60620;200.17149;-98.01260;,
 99.60620;0.17150;-98.01260;,
 5.50580;0.17150;-97.66850;,
 -96.34490;201.29410;98.68460;,
 -96.22550;0.17150;101.47670;,
 -96.13670;200.17149;98.77310;,
 -96.10450;200.17149;0.00000;,
 -100.00000;0.17150;0.00000;,
 -97.52120;0.17150;98.77310;,
 -69.65620;200.17149;-71.73910;,
 -69.65620;0.17150;-71.73910;,
 5.50580;200.17149;-97.66850;,
 5.50580;0.17150;-97.66850;,
 0.00000;200.17149;0.00000;,
 0.00000;200.17149;0.00000;,
 0.00000;200.17149;0.00000;,
 0.00000;200.17149;0.00000;,
 0.00000;200.17149;0.00000;,
 0.00000;0.17150;0.00000;,
 0.00000;0.17150;0.00000;,
 0.00000;0.17150;0.00000;,
 0.00000;0.17150;0.00000;,
 0.00000;0.17150;0.00000;;
 
 15;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;7,10,11,8;,
 4;10,12,13,11;,
 3;14,1,0;,
 3;15,4,1;,
 3;16,7,6;,
 3;17,10,7;,
 3;18,12,10;,
 3;19,3,2;,
 3;20,2,5;,
 3;21,9,8;,
 3;22,8,11;,
 3;23,11,13;;
 
 MeshMaterialList {
  2;
  15;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "DATA\\TEXTURE\\tumiki_Yellow.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  11;
  -0.053377;0.997100;-0.054245;,
  -0.167138;0.000000;-0.985933;,
  -0.003657;0.000000;-0.999993;,
  0.711029;0.005074;0.703144;,
  -0.999836;0.013196;0.012380;,
  -0.983393;0.011297;-0.181137;,
  -0.691190;0.004937;-0.722656;,
  0.000000;-1.000000;-0.000000;,
  -0.134354;0.981482;-0.136539;,
  0.000000;1.000000;0.000000;,
  -0.263732;0.926612;-0.268020;;
  15;
  4;1,2,2,1;,
  4;3,3,3,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,1,1,6;,
  3;0,8,9;,
  3;0,10,8;,
  3;0,9,9;,
  3;0,9,9;,
  3;0,9,9;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;;
 }
 MeshTextureCoords {
  24;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.625000;0.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.625000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
