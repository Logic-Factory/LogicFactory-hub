// Benchmark "dec" written by ABC on Mon Sep 11 23:29:10 2023

module dec ( 
    \count[0] , \count[1] , \count[2] , \count[3] , \count[4] , \count[5] ,
    \count[6] , \count[7] ,
    \selectp1[0] , \selectp1[1] , \selectp1[2] , \selectp1[3] ,
    \selectp1[4] , \selectp1[5] , \selectp1[6] , \selectp1[7] ,
    \selectp1[8] , \selectp1[9] , \selectp1[10] , \selectp1[11] ,
    \selectp1[12] , \selectp1[13] , \selectp1[14] , \selectp1[15] ,
    \selectp1[16] , \selectp1[17] , \selectp1[18] , \selectp1[19] ,
    \selectp1[20] , \selectp1[21] , \selectp1[22] , \selectp1[23] ,
    \selectp1[24] , \selectp1[25] , \selectp1[26] , \selectp1[27] ,
    \selectp1[28] , \selectp1[29] , \selectp1[30] , \selectp1[31] ,
    \selectp1[32] , \selectp1[33] , \selectp1[34] , \selectp1[35] ,
    \selectp1[36] , \selectp1[37] , \selectp1[38] , \selectp1[39] ,
    \selectp1[40] , \selectp1[41] , \selectp1[42] , \selectp1[43] ,
    \selectp1[44] , \selectp1[45] , \selectp1[46] , \selectp1[47] ,
    \selectp1[48] , \selectp1[49] , \selectp1[50] , \selectp1[51] ,
    \selectp1[52] , \selectp1[53] , \selectp1[54] , \selectp1[55] ,
    \selectp1[56] , \selectp1[57] , \selectp1[58] , \selectp1[59] ,
    \selectp1[60] , \selectp1[61] , \selectp1[62] , \selectp1[63] ,
    \selectp1[64] , \selectp1[65] , \selectp1[66] , \selectp1[67] ,
    \selectp1[68] , \selectp1[69] , \selectp1[70] , \selectp1[71] ,
    \selectp1[72] , \selectp1[73] , \selectp1[74] , \selectp1[75] ,
    \selectp1[76] , \selectp1[77] , \selectp1[78] , \selectp1[79] ,
    \selectp1[80] , \selectp1[81] , \selectp1[82] , \selectp1[83] ,
    \selectp1[84] , \selectp1[85] , \selectp1[86] , \selectp1[87] ,
    \selectp1[88] , \selectp1[89] , \selectp1[90] , \selectp1[91] ,
    \selectp1[92] , \selectp1[93] , \selectp1[94] , \selectp1[95] ,
    \selectp1[96] , \selectp1[97] , \selectp1[98] , \selectp1[99] ,
    \selectp1[100] , \selectp1[101] , \selectp1[102] , \selectp1[103] ,
    \selectp1[104] , \selectp1[105] , \selectp1[106] , \selectp1[107] ,
    \selectp1[108] , \selectp1[109] , \selectp1[110] , \selectp1[111] ,
    \selectp1[112] , \selectp1[113] , \selectp1[114] , \selectp1[115] ,
    \selectp1[116] , \selectp1[117] , \selectp1[118] , \selectp1[119] ,
    \selectp1[120] , \selectp1[121] , \selectp1[122] , \selectp1[123] ,
    \selectp1[124] , \selectp1[125] , \selectp1[126] , \selectp1[127] ,
    \selectp2[0] , \selectp2[1] , \selectp2[2] , \selectp2[3] ,
    \selectp2[4] , \selectp2[5] , \selectp2[6] , \selectp2[7] ,
    \selectp2[8] , \selectp2[9] , \selectp2[10] , \selectp2[11] ,
    \selectp2[12] , \selectp2[13] , \selectp2[14] , \selectp2[15] ,
    \selectp2[16] , \selectp2[17] , \selectp2[18] , \selectp2[19] ,
    \selectp2[20] , \selectp2[21] , \selectp2[22] , \selectp2[23] ,
    \selectp2[24] , \selectp2[25] , \selectp2[26] , \selectp2[27] ,
    \selectp2[28] , \selectp2[29] , \selectp2[30] , \selectp2[31] ,
    \selectp2[32] , \selectp2[33] , \selectp2[34] , \selectp2[35] ,
    \selectp2[36] , \selectp2[37] , \selectp2[38] , \selectp2[39] ,
    \selectp2[40] , \selectp2[41] , \selectp2[42] , \selectp2[43] ,
    \selectp2[44] , \selectp2[45] , \selectp2[46] , \selectp2[47] ,
    \selectp2[48] , \selectp2[49] , \selectp2[50] , \selectp2[51] ,
    \selectp2[52] , \selectp2[53] , \selectp2[54] , \selectp2[55] ,
    \selectp2[56] , \selectp2[57] , \selectp2[58] , \selectp2[59] ,
    \selectp2[60] , \selectp2[61] , \selectp2[62] , \selectp2[63] ,
    \selectp2[64] , \selectp2[65] , \selectp2[66] , \selectp2[67] ,
    \selectp2[68] , \selectp2[69] , \selectp2[70] , \selectp2[71] ,
    \selectp2[72] , \selectp2[73] , \selectp2[74] , \selectp2[75] ,
    \selectp2[76] , \selectp2[77] , \selectp2[78] , \selectp2[79] ,
    \selectp2[80] , \selectp2[81] , \selectp2[82] , \selectp2[83] ,
    \selectp2[84] , \selectp2[85] , \selectp2[86] , \selectp2[87] ,
    \selectp2[88] , \selectp2[89] , \selectp2[90] , \selectp2[91] ,
    \selectp2[92] , \selectp2[93] , \selectp2[94] , \selectp2[95] ,
    \selectp2[96] , \selectp2[97] , \selectp2[98] , \selectp2[99] ,
    \selectp2[100] , \selectp2[101] , \selectp2[102] , \selectp2[103] ,
    \selectp2[104] , \selectp2[105] , \selectp2[106] , \selectp2[107] ,
    \selectp2[108] , \selectp2[109] , \selectp2[110] , \selectp2[111] ,
    \selectp2[112] , \selectp2[113] , \selectp2[114] , \selectp2[115] ,
    \selectp2[116] , \selectp2[117] , \selectp2[118] , \selectp2[119] ,
    \selectp2[120] , \selectp2[121] , \selectp2[122] , \selectp2[123] ,
    \selectp2[124] , \selectp2[125] , \selectp2[126] , \selectp2[127]   );
  input  \count[0] , \count[1] , \count[2] , \count[3] , \count[4] ,
    \count[5] , \count[6] , \count[7] ;
  output \selectp1[0] , \selectp1[1] , \selectp1[2] , \selectp1[3] ,
    \selectp1[4] , \selectp1[5] , \selectp1[6] , \selectp1[7] ,
    \selectp1[8] , \selectp1[9] , \selectp1[10] , \selectp1[11] ,
    \selectp1[12] , \selectp1[13] , \selectp1[14] , \selectp1[15] ,
    \selectp1[16] , \selectp1[17] , \selectp1[18] , \selectp1[19] ,
    \selectp1[20] , \selectp1[21] , \selectp1[22] , \selectp1[23] ,
    \selectp1[24] , \selectp1[25] , \selectp1[26] , \selectp1[27] ,
    \selectp1[28] , \selectp1[29] , \selectp1[30] , \selectp1[31] ,
    \selectp1[32] , \selectp1[33] , \selectp1[34] , \selectp1[35] ,
    \selectp1[36] , \selectp1[37] , \selectp1[38] , \selectp1[39] ,
    \selectp1[40] , \selectp1[41] , \selectp1[42] , \selectp1[43] ,
    \selectp1[44] , \selectp1[45] , \selectp1[46] , \selectp1[47] ,
    \selectp1[48] , \selectp1[49] , \selectp1[50] , \selectp1[51] ,
    \selectp1[52] , \selectp1[53] , \selectp1[54] , \selectp1[55] ,
    \selectp1[56] , \selectp1[57] , \selectp1[58] , \selectp1[59] ,
    \selectp1[60] , \selectp1[61] , \selectp1[62] , \selectp1[63] ,
    \selectp1[64] , \selectp1[65] , \selectp1[66] , \selectp1[67] ,
    \selectp1[68] , \selectp1[69] , \selectp1[70] , \selectp1[71] ,
    \selectp1[72] , \selectp1[73] , \selectp1[74] , \selectp1[75] ,
    \selectp1[76] , \selectp1[77] , \selectp1[78] , \selectp1[79] ,
    \selectp1[80] , \selectp1[81] , \selectp1[82] , \selectp1[83] ,
    \selectp1[84] , \selectp1[85] , \selectp1[86] , \selectp1[87] ,
    \selectp1[88] , \selectp1[89] , \selectp1[90] , \selectp1[91] ,
    \selectp1[92] , \selectp1[93] , \selectp1[94] , \selectp1[95] ,
    \selectp1[96] , \selectp1[97] , \selectp1[98] , \selectp1[99] ,
    \selectp1[100] , \selectp1[101] , \selectp1[102] , \selectp1[103] ,
    \selectp1[104] , \selectp1[105] , \selectp1[106] , \selectp1[107] ,
    \selectp1[108] , \selectp1[109] , \selectp1[110] , \selectp1[111] ,
    \selectp1[112] , \selectp1[113] , \selectp1[114] , \selectp1[115] ,
    \selectp1[116] , \selectp1[117] , \selectp1[118] , \selectp1[119] ,
    \selectp1[120] , \selectp1[121] , \selectp1[122] , \selectp1[123] ,
    \selectp1[124] , \selectp1[125] , \selectp1[126] , \selectp1[127] ,
    \selectp2[0] , \selectp2[1] , \selectp2[2] , \selectp2[3] ,
    \selectp2[4] , \selectp2[5] , \selectp2[6] , \selectp2[7] ,
    \selectp2[8] , \selectp2[9] , \selectp2[10] , \selectp2[11] ,
    \selectp2[12] , \selectp2[13] , \selectp2[14] , \selectp2[15] ,
    \selectp2[16] , \selectp2[17] , \selectp2[18] , \selectp2[19] ,
    \selectp2[20] , \selectp2[21] , \selectp2[22] , \selectp2[23] ,
    \selectp2[24] , \selectp2[25] , \selectp2[26] , \selectp2[27] ,
    \selectp2[28] , \selectp2[29] , \selectp2[30] , \selectp2[31] ,
    \selectp2[32] , \selectp2[33] , \selectp2[34] , \selectp2[35] ,
    \selectp2[36] , \selectp2[37] , \selectp2[38] , \selectp2[39] ,
    \selectp2[40] , \selectp2[41] , \selectp2[42] , \selectp2[43] ,
    \selectp2[44] , \selectp2[45] , \selectp2[46] , \selectp2[47] ,
    \selectp2[48] , \selectp2[49] , \selectp2[50] , \selectp2[51] ,
    \selectp2[52] , \selectp2[53] , \selectp2[54] , \selectp2[55] ,
    \selectp2[56] , \selectp2[57] , \selectp2[58] , \selectp2[59] ,
    \selectp2[60] , \selectp2[61] , \selectp2[62] , \selectp2[63] ,
    \selectp2[64] , \selectp2[65] , \selectp2[66] , \selectp2[67] ,
    \selectp2[68] , \selectp2[69] , \selectp2[70] , \selectp2[71] ,
    \selectp2[72] , \selectp2[73] , \selectp2[74] , \selectp2[75] ,
    \selectp2[76] , \selectp2[77] , \selectp2[78] , \selectp2[79] ,
    \selectp2[80] , \selectp2[81] , \selectp2[82] , \selectp2[83] ,
    \selectp2[84] , \selectp2[85] , \selectp2[86] , \selectp2[87] ,
    \selectp2[88] , \selectp2[89] , \selectp2[90] , \selectp2[91] ,
    \selectp2[92] , \selectp2[93] , \selectp2[94] , \selectp2[95] ,
    \selectp2[96] , \selectp2[97] , \selectp2[98] , \selectp2[99] ,
    \selectp2[100] , \selectp2[101] , \selectp2[102] , \selectp2[103] ,
    \selectp2[104] , \selectp2[105] , \selectp2[106] , \selectp2[107] ,
    \selectp2[108] , \selectp2[109] , \selectp2[110] , \selectp2[111] ,
    \selectp2[112] , \selectp2[113] , \selectp2[114] , \selectp2[115] ,
    \selectp2[116] , \selectp2[117] , \selectp2[118] , \selectp2[119] ,
    \selectp2[120] , \selectp2[121] , \selectp2[122] , \selectp2[123] ,
    \selectp2[124] , \selectp2[125] , \selectp2[126] , \selectp2[127] ;
  wire new_n265_, new_n266_, new_n267_, new_n268_, new_n269_, new_n270_,
    new_n271_, new_n273_, new_n274_, new_n275_, new_n277_, new_n279_,
    new_n281_, new_n282_, new_n284_, new_n286_, new_n288_, new_n290_,
    new_n292_, new_n294_, new_n296_, new_n298_, new_n300_, new_n302_,
    new_n304_, new_n306_, new_n307_, new_n324_, new_n325_, new_n342_,
    new_n359_, new_n376_, new_n393_, new_n410_, new_n427_, new_n428_,
    new_n445_, new_n446_, new_n463_, new_n480_, new_n497_, new_n514_,
    new_n531_, new_n548_;
  INV_X1     g000(.I(\count[6] ), .ZN(new_n265_));
  NOR2_X1    g001(.A1(\count[4] ), .A2(\count[5] ), .ZN(new_n266_));
  NAND3_X1   g002(.A1(new_n266_), .A2(new_n265_), .A3(\count[7] ), .ZN(new_n267_));
  INV_X1     g003(.I(\count[1] ), .ZN(new_n268_));
  INV_X1     g004(.I(\count[3] ), .ZN(new_n269_));
  NOR2_X1    g005(.A1(\count[0] ), .A2(\count[2] ), .ZN(new_n270_));
  NAND3_X1   g006(.A1(new_n270_), .A2(new_n268_), .A3(new_n269_), .ZN(new_n271_));
  NOR2_X1    g007(.A1(new_n267_), .A2(new_n271_), .ZN(\selectp1[0] ));
  INV_X1     g008(.I(\count[2] ), .ZN(new_n273_));
  NOR2_X1    g009(.A1(\count[1] ), .A2(\count[3] ), .ZN(new_n274_));
  NAND3_X1   g010(.A1(new_n274_), .A2(\count[0] ), .A3(new_n273_), .ZN(new_n275_));
  NOR2_X1    g011(.A1(new_n267_), .A2(new_n275_), .ZN(\selectp1[1] ));
  NAND3_X1   g012(.A1(new_n270_), .A2(\count[1] ), .A3(new_n269_), .ZN(new_n277_));
  NOR2_X1    g013(.A1(new_n267_), .A2(new_n277_), .ZN(\selectp1[2] ));
  NAND4_X1   g014(.A1(new_n273_), .A2(new_n269_), .A3(\count[0] ), .A4(\count[1] ), .ZN(new_n279_));
  NOR2_X1    g015(.A1(new_n267_), .A2(new_n279_), .ZN(\selectp1[3] ));
  INV_X1     g016(.I(\count[0] ), .ZN(new_n281_));
  NAND3_X1   g017(.A1(new_n274_), .A2(new_n281_), .A3(\count[2] ), .ZN(new_n282_));
  NOR2_X1    g018(.A1(new_n267_), .A2(new_n282_), .ZN(\selectp1[4] ));
  NAND3_X1   g019(.A1(new_n274_), .A2(\count[0] ), .A3(\count[2] ), .ZN(new_n284_));
  NOR2_X1    g020(.A1(new_n267_), .A2(new_n284_), .ZN(\selectp1[5] ));
  NAND4_X1   g021(.A1(new_n281_), .A2(new_n269_), .A3(\count[1] ), .A4(\count[2] ), .ZN(new_n286_));
  NOR2_X1    g022(.A1(new_n267_), .A2(new_n286_), .ZN(\selectp1[6] ));
  NAND4_X1   g023(.A1(new_n269_), .A2(\count[0] ), .A3(\count[1] ), .A4(\count[2] ), .ZN(new_n288_));
  NOR2_X1    g024(.A1(new_n267_), .A2(new_n288_), .ZN(\selectp1[7] ));
  NAND3_X1   g025(.A1(new_n270_), .A2(new_n268_), .A3(\count[3] ), .ZN(new_n290_));
  NOR2_X1    g026(.A1(new_n267_), .A2(new_n290_), .ZN(\selectp1[8] ));
  NAND4_X1   g027(.A1(new_n268_), .A2(new_n273_), .A3(\count[0] ), .A4(\count[3] ), .ZN(new_n292_));
  NOR2_X1    g028(.A1(new_n267_), .A2(new_n292_), .ZN(\selectp1[9] ));
  NAND3_X1   g029(.A1(new_n270_), .A2(\count[1] ), .A3(\count[3] ), .ZN(new_n294_));
  NOR2_X1    g030(.A1(new_n267_), .A2(new_n294_), .ZN(\selectp1[10] ));
  NAND4_X1   g031(.A1(new_n273_), .A2(\count[0] ), .A3(\count[1] ), .A4(\count[3] ), .ZN(new_n296_));
  NOR2_X1    g032(.A1(new_n267_), .A2(new_n296_), .ZN(\selectp1[11] ));
  NAND4_X1   g033(.A1(new_n281_), .A2(new_n268_), .A3(\count[2] ), .A4(\count[3] ), .ZN(new_n298_));
  NOR2_X1    g034(.A1(new_n267_), .A2(new_n298_), .ZN(\selectp1[12] ));
  NAND4_X1   g035(.A1(new_n268_), .A2(\count[0] ), .A3(\count[2] ), .A4(\count[3] ), .ZN(new_n300_));
  NOR2_X1    g036(.A1(new_n267_), .A2(new_n300_), .ZN(\selectp1[13] ));
  NAND4_X1   g037(.A1(new_n281_), .A2(\count[1] ), .A3(\count[2] ), .A4(\count[3] ), .ZN(new_n302_));
  NOR2_X1    g038(.A1(new_n267_), .A2(new_n302_), .ZN(\selectp1[14] ));
  NAND4_X1   g039(.A1(\count[0] ), .A2(\count[1] ), .A3(\count[2] ), .A4(\count[3] ), .ZN(new_n304_));
  NOR2_X1    g040(.A1(new_n267_), .A2(new_n304_), .ZN(\selectp1[15] ));
  INV_X1     g041(.I(\count[5] ), .ZN(new_n306_));
  NAND4_X1   g042(.A1(new_n306_), .A2(new_n265_), .A3(\count[4] ), .A4(\count[7] ), .ZN(new_n307_));
  NOR2_X1    g043(.A1(new_n271_), .A2(new_n307_), .ZN(\selectp1[16] ));
  NOR2_X1    g044(.A1(new_n275_), .A2(new_n307_), .ZN(\selectp1[17] ));
  NOR2_X1    g045(.A1(new_n277_), .A2(new_n307_), .ZN(\selectp1[18] ));
  NOR2_X1    g046(.A1(new_n279_), .A2(new_n307_), .ZN(\selectp1[19] ));
  NOR2_X1    g047(.A1(new_n282_), .A2(new_n307_), .ZN(\selectp1[20] ));
  NOR2_X1    g048(.A1(new_n284_), .A2(new_n307_), .ZN(\selectp1[21] ));
  NOR2_X1    g049(.A1(new_n286_), .A2(new_n307_), .ZN(\selectp1[22] ));
  NOR2_X1    g050(.A1(new_n307_), .A2(new_n288_), .ZN(\selectp1[23] ));
  NOR2_X1    g051(.A1(new_n290_), .A2(new_n307_), .ZN(\selectp1[24] ));
  NOR2_X1    g052(.A1(new_n292_), .A2(new_n307_), .ZN(\selectp1[25] ));
  NOR2_X1    g053(.A1(new_n294_), .A2(new_n307_), .ZN(\selectp1[26] ));
  NOR2_X1    g054(.A1(new_n307_), .A2(new_n296_), .ZN(\selectp1[27] ));
  NOR2_X1    g055(.A1(new_n298_), .A2(new_n307_), .ZN(\selectp1[28] ));
  NOR2_X1    g056(.A1(new_n307_), .A2(new_n300_), .ZN(\selectp1[29] ));
  NOR2_X1    g057(.A1(new_n307_), .A2(new_n302_), .ZN(\selectp1[30] ));
  NOR2_X1    g058(.A1(new_n307_), .A2(new_n304_), .ZN(\selectp1[31] ));
  INV_X1     g059(.I(\count[4] ), .ZN(new_n324_));
  NAND4_X1   g060(.A1(new_n324_), .A2(new_n265_), .A3(\count[5] ), .A4(\count[7] ), .ZN(new_n325_));
  NOR2_X1    g061(.A1(new_n271_), .A2(new_n325_), .ZN(\selectp1[32] ));
  NOR2_X1    g062(.A1(new_n275_), .A2(new_n325_), .ZN(\selectp1[33] ));
  NOR2_X1    g063(.A1(new_n277_), .A2(new_n325_), .ZN(\selectp1[34] ));
  NOR2_X1    g064(.A1(new_n279_), .A2(new_n325_), .ZN(\selectp1[35] ));
  NOR2_X1    g065(.A1(new_n282_), .A2(new_n325_), .ZN(\selectp1[36] ));
  NOR2_X1    g066(.A1(new_n284_), .A2(new_n325_), .ZN(\selectp1[37] ));
  NOR2_X1    g067(.A1(new_n286_), .A2(new_n325_), .ZN(\selectp1[38] ));
  NOR2_X1    g068(.A1(new_n325_), .A2(new_n288_), .ZN(\selectp1[39] ));
  NOR2_X1    g069(.A1(new_n290_), .A2(new_n325_), .ZN(\selectp1[40] ));
  NOR2_X1    g070(.A1(new_n292_), .A2(new_n325_), .ZN(\selectp1[41] ));
  NOR2_X1    g071(.A1(new_n294_), .A2(new_n325_), .ZN(\selectp1[42] ));
  NOR2_X1    g072(.A1(new_n325_), .A2(new_n296_), .ZN(\selectp1[43] ));
  NOR2_X1    g073(.A1(new_n298_), .A2(new_n325_), .ZN(\selectp1[44] ));
  NOR2_X1    g074(.A1(new_n325_), .A2(new_n300_), .ZN(\selectp1[45] ));
  NOR2_X1    g075(.A1(new_n325_), .A2(new_n302_), .ZN(\selectp1[46] ));
  NOR2_X1    g076(.A1(new_n325_), .A2(new_n304_), .ZN(\selectp1[47] ));
  NAND4_X1   g077(.A1(new_n265_), .A2(\count[4] ), .A3(\count[5] ), .A4(\count[7] ), .ZN(new_n342_));
  NOR2_X1    g078(.A1(new_n271_), .A2(new_n342_), .ZN(\selectp1[48] ));
  NOR2_X1    g079(.A1(new_n275_), .A2(new_n342_), .ZN(\selectp1[49] ));
  NOR2_X1    g080(.A1(new_n277_), .A2(new_n342_), .ZN(\selectp1[50] ));
  NOR2_X1    g081(.A1(new_n279_), .A2(new_n342_), .ZN(\selectp1[51] ));
  NOR2_X1    g082(.A1(new_n282_), .A2(new_n342_), .ZN(\selectp1[52] ));
  NOR2_X1    g083(.A1(new_n284_), .A2(new_n342_), .ZN(\selectp1[53] ));
  NOR2_X1    g084(.A1(new_n286_), .A2(new_n342_), .ZN(\selectp1[54] ));
  NOR2_X1    g085(.A1(new_n288_), .A2(new_n342_), .ZN(\selectp1[55] ));
  NOR2_X1    g086(.A1(new_n290_), .A2(new_n342_), .ZN(\selectp1[56] ));
  NOR2_X1    g087(.A1(new_n292_), .A2(new_n342_), .ZN(\selectp1[57] ));
  NOR2_X1    g088(.A1(new_n294_), .A2(new_n342_), .ZN(\selectp1[58] ));
  NOR2_X1    g089(.A1(new_n296_), .A2(new_n342_), .ZN(\selectp1[59] ));
  NOR2_X1    g090(.A1(new_n298_), .A2(new_n342_), .ZN(\selectp1[60] ));
  NOR2_X1    g091(.A1(new_n300_), .A2(new_n342_), .ZN(\selectp1[61] ));
  NOR2_X1    g092(.A1(new_n302_), .A2(new_n342_), .ZN(\selectp1[62] ));
  NOR2_X1    g093(.A1(new_n342_), .A2(new_n304_), .ZN(\selectp1[63] ));
  NAND3_X1   g094(.A1(new_n266_), .A2(\count[6] ), .A3(\count[7] ), .ZN(new_n359_));
  NOR2_X1    g095(.A1(new_n271_), .A2(new_n359_), .ZN(\selectp1[64] ));
  NOR2_X1    g096(.A1(new_n275_), .A2(new_n359_), .ZN(\selectp1[65] ));
  NOR2_X1    g097(.A1(new_n277_), .A2(new_n359_), .ZN(\selectp1[66] ));
  NOR2_X1    g098(.A1(new_n359_), .A2(new_n279_), .ZN(\selectp1[67] ));
  NOR2_X1    g099(.A1(new_n282_), .A2(new_n359_), .ZN(\selectp1[68] ));
  NOR2_X1    g100(.A1(new_n284_), .A2(new_n359_), .ZN(\selectp1[69] ));
  NOR2_X1    g101(.A1(new_n359_), .A2(new_n286_), .ZN(\selectp1[70] ));
  NOR2_X1    g102(.A1(new_n359_), .A2(new_n288_), .ZN(\selectp1[71] ));
  NOR2_X1    g103(.A1(new_n290_), .A2(new_n359_), .ZN(\selectp1[72] ));
  NOR2_X1    g104(.A1(new_n359_), .A2(new_n292_), .ZN(\selectp1[73] ));
  NOR2_X1    g105(.A1(new_n294_), .A2(new_n359_), .ZN(\selectp1[74] ));
  NOR2_X1    g106(.A1(new_n359_), .A2(new_n296_), .ZN(\selectp1[75] ));
  NOR2_X1    g107(.A1(new_n359_), .A2(new_n298_), .ZN(\selectp1[76] ));
  NOR2_X1    g108(.A1(new_n359_), .A2(new_n300_), .ZN(\selectp1[77] ));
  NOR2_X1    g109(.A1(new_n359_), .A2(new_n302_), .ZN(\selectp1[78] ));
  NOR2_X1    g110(.A1(new_n359_), .A2(new_n304_), .ZN(\selectp1[79] ));
  NAND4_X1   g111(.A1(new_n306_), .A2(\count[4] ), .A3(\count[6] ), .A4(\count[7] ), .ZN(new_n376_));
  NOR2_X1    g112(.A1(new_n271_), .A2(new_n376_), .ZN(\selectp1[80] ));
  NOR2_X1    g113(.A1(new_n275_), .A2(new_n376_), .ZN(\selectp1[81] ));
  NOR2_X1    g114(.A1(new_n277_), .A2(new_n376_), .ZN(\selectp1[82] ));
  NOR2_X1    g115(.A1(new_n279_), .A2(new_n376_), .ZN(\selectp1[83] ));
  NOR2_X1    g116(.A1(new_n282_), .A2(new_n376_), .ZN(\selectp1[84] ));
  NOR2_X1    g117(.A1(new_n284_), .A2(new_n376_), .ZN(\selectp1[85] ));
  NOR2_X1    g118(.A1(new_n286_), .A2(new_n376_), .ZN(\selectp1[86] ));
  NOR2_X1    g119(.A1(new_n288_), .A2(new_n376_), .ZN(\selectp1[87] ));
  NOR2_X1    g120(.A1(new_n290_), .A2(new_n376_), .ZN(\selectp1[88] ));
  NOR2_X1    g121(.A1(new_n292_), .A2(new_n376_), .ZN(\selectp1[89] ));
  NOR2_X1    g122(.A1(new_n294_), .A2(new_n376_), .ZN(\selectp1[90] ));
  NOR2_X1    g123(.A1(new_n296_), .A2(new_n376_), .ZN(\selectp1[91] ));
  NOR2_X1    g124(.A1(new_n298_), .A2(new_n376_), .ZN(\selectp1[92] ));
  NOR2_X1    g125(.A1(new_n300_), .A2(new_n376_), .ZN(\selectp1[93] ));
  NOR2_X1    g126(.A1(new_n302_), .A2(new_n376_), .ZN(\selectp1[94] ));
  NOR2_X1    g127(.A1(new_n376_), .A2(new_n304_), .ZN(\selectp1[95] ));
  NAND4_X1   g128(.A1(new_n324_), .A2(\count[5] ), .A3(\count[6] ), .A4(\count[7] ), .ZN(new_n393_));
  NOR2_X1    g129(.A1(new_n271_), .A2(new_n393_), .ZN(\selectp1[96] ));
  NOR2_X1    g130(.A1(new_n275_), .A2(new_n393_), .ZN(\selectp1[97] ));
  NOR2_X1    g131(.A1(new_n277_), .A2(new_n393_), .ZN(\selectp1[98] ));
  NOR2_X1    g132(.A1(new_n279_), .A2(new_n393_), .ZN(\selectp1[99] ));
  NOR2_X1    g133(.A1(new_n282_), .A2(new_n393_), .ZN(\selectp1[100] ));
  NOR2_X1    g134(.A1(new_n284_), .A2(new_n393_), .ZN(\selectp1[101] ));
  NOR2_X1    g135(.A1(new_n286_), .A2(new_n393_), .ZN(\selectp1[102] ));
  NOR2_X1    g136(.A1(new_n288_), .A2(new_n393_), .ZN(\selectp1[103] ));
  NOR2_X1    g137(.A1(new_n290_), .A2(new_n393_), .ZN(\selectp1[104] ));
  NOR2_X1    g138(.A1(new_n292_), .A2(new_n393_), .ZN(\selectp1[105] ));
  NOR2_X1    g139(.A1(new_n294_), .A2(new_n393_), .ZN(\selectp1[106] ));
  NOR2_X1    g140(.A1(new_n296_), .A2(new_n393_), .ZN(\selectp1[107] ));
  NOR2_X1    g141(.A1(new_n298_), .A2(new_n393_), .ZN(\selectp1[108] ));
  NOR2_X1    g142(.A1(new_n300_), .A2(new_n393_), .ZN(\selectp1[109] ));
  NOR2_X1    g143(.A1(new_n302_), .A2(new_n393_), .ZN(\selectp1[110] ));
  NOR2_X1    g144(.A1(new_n393_), .A2(new_n304_), .ZN(\selectp1[111] ));
  NAND4_X1   g145(.A1(\count[4] ), .A2(\count[5] ), .A3(\count[6] ), .A4(\count[7] ), .ZN(new_n410_));
  NOR2_X1    g146(.A1(new_n271_), .A2(new_n410_), .ZN(\selectp1[112] ));
  NOR2_X1    g147(.A1(new_n275_), .A2(new_n410_), .ZN(\selectp1[113] ));
  NOR2_X1    g148(.A1(new_n277_), .A2(new_n410_), .ZN(\selectp1[114] ));
  NOR2_X1    g149(.A1(new_n279_), .A2(new_n410_), .ZN(\selectp1[115] ));
  NOR2_X1    g150(.A1(new_n282_), .A2(new_n410_), .ZN(\selectp1[116] ));
  NOR2_X1    g151(.A1(new_n284_), .A2(new_n410_), .ZN(\selectp1[117] ));
  NOR2_X1    g152(.A1(new_n286_), .A2(new_n410_), .ZN(\selectp1[118] ));
  NOR2_X1    g153(.A1(new_n288_), .A2(new_n410_), .ZN(\selectp1[119] ));
  NOR2_X1    g154(.A1(new_n290_), .A2(new_n410_), .ZN(\selectp1[120] ));
  NOR2_X1    g155(.A1(new_n292_), .A2(new_n410_), .ZN(\selectp1[121] ));
  NOR2_X1    g156(.A1(new_n294_), .A2(new_n410_), .ZN(\selectp1[122] ));
  NOR2_X1    g157(.A1(new_n296_), .A2(new_n410_), .ZN(\selectp1[123] ));
  NOR2_X1    g158(.A1(new_n298_), .A2(new_n410_), .ZN(\selectp1[124] ));
  NOR2_X1    g159(.A1(new_n300_), .A2(new_n410_), .ZN(\selectp1[125] ));
  NOR2_X1    g160(.A1(new_n302_), .A2(new_n410_), .ZN(\selectp1[126] ));
  NOR2_X1    g161(.A1(new_n304_), .A2(new_n410_), .ZN(\selectp1[127] ));
  INV_X1     g162(.I(\count[7] ), .ZN(new_n427_));
  NAND3_X1   g163(.A1(new_n266_), .A2(new_n265_), .A3(new_n427_), .ZN(new_n428_));
  NOR2_X1    g164(.A1(new_n271_), .A2(new_n428_), .ZN(\selectp2[0] ));
  NOR2_X1    g165(.A1(new_n275_), .A2(new_n428_), .ZN(\selectp2[1] ));
  NOR2_X1    g166(.A1(new_n277_), .A2(new_n428_), .ZN(\selectp2[2] ));
  NOR2_X1    g167(.A1(new_n428_), .A2(new_n279_), .ZN(\selectp2[3] ));
  NOR2_X1    g168(.A1(new_n282_), .A2(new_n428_), .ZN(\selectp2[4] ));
  NOR2_X1    g169(.A1(new_n428_), .A2(new_n284_), .ZN(\selectp2[5] ));
  NOR2_X1    g170(.A1(new_n428_), .A2(new_n286_), .ZN(\selectp2[6] ));
  NOR2_X1    g171(.A1(new_n428_), .A2(new_n288_), .ZN(\selectp2[7] ));
  NOR2_X1    g172(.A1(new_n290_), .A2(new_n428_), .ZN(\selectp2[8] ));
  NOR2_X1    g173(.A1(new_n428_), .A2(new_n292_), .ZN(\selectp2[9] ));
  NOR2_X1    g174(.A1(new_n428_), .A2(new_n294_), .ZN(\selectp2[10] ));
  NOR2_X1    g175(.A1(new_n428_), .A2(new_n296_), .ZN(\selectp2[11] ));
  NOR2_X1    g176(.A1(new_n428_), .A2(new_n298_), .ZN(\selectp2[12] ));
  NOR2_X1    g177(.A1(new_n428_), .A2(new_n300_), .ZN(\selectp2[13] ));
  NOR2_X1    g178(.A1(new_n428_), .A2(new_n302_), .ZN(\selectp2[14] ));
  NOR2_X1    g179(.A1(new_n428_), .A2(new_n304_), .ZN(\selectp2[15] ));
  NOR2_X1    g180(.A1(\count[6] ), .A2(\count[7] ), .ZN(new_n445_));
  NAND3_X1   g181(.A1(new_n445_), .A2(\count[4] ), .A3(new_n306_), .ZN(new_n446_));
  NOR2_X1    g182(.A1(new_n271_), .A2(new_n446_), .ZN(\selectp2[16] ));
  NOR2_X1    g183(.A1(new_n275_), .A2(new_n446_), .ZN(\selectp2[17] ));
  NOR2_X1    g184(.A1(new_n277_), .A2(new_n446_), .ZN(\selectp2[18] ));
  NOR2_X1    g185(.A1(new_n446_), .A2(new_n279_), .ZN(\selectp2[19] ));
  NOR2_X1    g186(.A1(new_n282_), .A2(new_n446_), .ZN(\selectp2[20] ));
  NOR2_X1    g187(.A1(new_n446_), .A2(new_n284_), .ZN(\selectp2[21] ));
  NOR2_X1    g188(.A1(new_n446_), .A2(new_n286_), .ZN(\selectp2[22] ));
  NOR2_X1    g189(.A1(new_n446_), .A2(new_n288_), .ZN(\selectp2[23] ));
  NOR2_X1    g190(.A1(new_n290_), .A2(new_n446_), .ZN(\selectp2[24] ));
  NOR2_X1    g191(.A1(new_n446_), .A2(new_n292_), .ZN(\selectp2[25] ));
  NOR2_X1    g192(.A1(new_n446_), .A2(new_n294_), .ZN(\selectp2[26] ));
  NOR2_X1    g193(.A1(new_n446_), .A2(new_n296_), .ZN(\selectp2[27] ));
  NOR2_X1    g194(.A1(new_n446_), .A2(new_n298_), .ZN(\selectp2[28] ));
  NOR2_X1    g195(.A1(new_n446_), .A2(new_n300_), .ZN(\selectp2[29] ));
  NOR2_X1    g196(.A1(new_n446_), .A2(new_n302_), .ZN(\selectp2[30] ));
  NOR2_X1    g197(.A1(new_n446_), .A2(new_n304_), .ZN(\selectp2[31] ));
  NAND3_X1   g198(.A1(new_n445_), .A2(new_n324_), .A3(\count[5] ), .ZN(new_n463_));
  NOR2_X1    g199(.A1(new_n271_), .A2(new_n463_), .ZN(\selectp2[32] ));
  NOR2_X1    g200(.A1(new_n275_), .A2(new_n463_), .ZN(\selectp2[33] ));
  NOR2_X1    g201(.A1(new_n277_), .A2(new_n463_), .ZN(\selectp2[34] ));
  NOR2_X1    g202(.A1(new_n463_), .A2(new_n279_), .ZN(\selectp2[35] ));
  NOR2_X1    g203(.A1(new_n282_), .A2(new_n463_), .ZN(\selectp2[36] ));
  NOR2_X1    g204(.A1(new_n463_), .A2(new_n284_), .ZN(\selectp2[37] ));
  NOR2_X1    g205(.A1(new_n463_), .A2(new_n286_), .ZN(\selectp2[38] ));
  NOR2_X1    g206(.A1(new_n463_), .A2(new_n288_), .ZN(\selectp2[39] ));
  NOR2_X1    g207(.A1(new_n290_), .A2(new_n463_), .ZN(\selectp2[40] ));
  NOR2_X1    g208(.A1(new_n463_), .A2(new_n292_), .ZN(\selectp2[41] ));
  NOR2_X1    g209(.A1(new_n463_), .A2(new_n294_), .ZN(\selectp2[42] ));
  NOR2_X1    g210(.A1(new_n463_), .A2(new_n296_), .ZN(\selectp2[43] ));
  NOR2_X1    g211(.A1(new_n463_), .A2(new_n298_), .ZN(\selectp2[44] ));
  NOR2_X1    g212(.A1(new_n463_), .A2(new_n300_), .ZN(\selectp2[45] ));
  NOR2_X1    g213(.A1(new_n463_), .A2(new_n302_), .ZN(\selectp2[46] ));
  NOR2_X1    g214(.A1(new_n463_), .A2(new_n304_), .ZN(\selectp2[47] ));
  NAND3_X1   g215(.A1(new_n445_), .A2(\count[4] ), .A3(\count[5] ), .ZN(new_n480_));
  NOR2_X1    g216(.A1(new_n271_), .A2(new_n480_), .ZN(\selectp2[48] ));
  NOR2_X1    g217(.A1(new_n275_), .A2(new_n480_), .ZN(\selectp2[49] ));
  NOR2_X1    g218(.A1(new_n277_), .A2(new_n480_), .ZN(\selectp2[50] ));
  NOR2_X1    g219(.A1(new_n480_), .A2(new_n279_), .ZN(\selectp2[51] ));
  NOR2_X1    g220(.A1(new_n282_), .A2(new_n480_), .ZN(\selectp2[52] ));
  NOR2_X1    g221(.A1(new_n284_), .A2(new_n480_), .ZN(\selectp2[53] ));
  NOR2_X1    g222(.A1(new_n480_), .A2(new_n286_), .ZN(\selectp2[54] ));
  NOR2_X1    g223(.A1(new_n480_), .A2(new_n288_), .ZN(\selectp2[55] ));
  NOR2_X1    g224(.A1(new_n290_), .A2(new_n480_), .ZN(\selectp2[56] ));
  NOR2_X1    g225(.A1(new_n480_), .A2(new_n292_), .ZN(\selectp2[57] ));
  NOR2_X1    g226(.A1(new_n294_), .A2(new_n480_), .ZN(\selectp2[58] ));
  NOR2_X1    g227(.A1(new_n480_), .A2(new_n296_), .ZN(\selectp2[59] ));
  NOR2_X1    g228(.A1(new_n480_), .A2(new_n298_), .ZN(\selectp2[60] ));
  NOR2_X1    g229(.A1(new_n480_), .A2(new_n300_), .ZN(\selectp2[61] ));
  NOR2_X1    g230(.A1(new_n480_), .A2(new_n302_), .ZN(\selectp2[62] ));
  NOR2_X1    g231(.A1(new_n480_), .A2(new_n304_), .ZN(\selectp2[63] ));
  NAND3_X1   g232(.A1(new_n266_), .A2(\count[6] ), .A3(new_n427_), .ZN(new_n497_));
  NOR2_X1    g233(.A1(new_n271_), .A2(new_n497_), .ZN(\selectp2[64] ));
  NOR2_X1    g234(.A1(new_n275_), .A2(new_n497_), .ZN(\selectp2[65] ));
  NOR2_X1    g235(.A1(new_n277_), .A2(new_n497_), .ZN(\selectp2[66] ));
  NOR2_X1    g236(.A1(new_n497_), .A2(new_n279_), .ZN(\selectp2[67] ));
  NOR2_X1    g237(.A1(new_n282_), .A2(new_n497_), .ZN(\selectp2[68] ));
  NOR2_X1    g238(.A1(new_n497_), .A2(new_n284_), .ZN(\selectp2[69] ));
  NOR2_X1    g239(.A1(new_n497_), .A2(new_n286_), .ZN(\selectp2[70] ));
  NOR2_X1    g240(.A1(new_n497_), .A2(new_n288_), .ZN(\selectp2[71] ));
  NOR2_X1    g241(.A1(new_n290_), .A2(new_n497_), .ZN(\selectp2[72] ));
  NOR2_X1    g242(.A1(new_n497_), .A2(new_n292_), .ZN(\selectp2[73] ));
  NOR2_X1    g243(.A1(new_n497_), .A2(new_n294_), .ZN(\selectp2[74] ));
  NOR2_X1    g244(.A1(new_n497_), .A2(new_n296_), .ZN(\selectp2[75] ));
  NOR2_X1    g245(.A1(new_n497_), .A2(new_n298_), .ZN(\selectp2[76] ));
  NOR2_X1    g246(.A1(new_n497_), .A2(new_n300_), .ZN(\selectp2[77] ));
  NOR2_X1    g247(.A1(new_n497_), .A2(new_n302_), .ZN(\selectp2[78] ));
  NOR2_X1    g248(.A1(new_n497_), .A2(new_n304_), .ZN(\selectp2[79] ));
  NAND4_X1   g249(.A1(new_n306_), .A2(new_n427_), .A3(\count[4] ), .A4(\count[6] ), .ZN(new_n514_));
  NOR2_X1    g250(.A1(new_n271_), .A2(new_n514_), .ZN(\selectp2[80] ));
  NOR2_X1    g251(.A1(new_n275_), .A2(new_n514_), .ZN(\selectp2[81] ));
  NOR2_X1    g252(.A1(new_n277_), .A2(new_n514_), .ZN(\selectp2[82] ));
  NOR2_X1    g253(.A1(new_n279_), .A2(new_n514_), .ZN(\selectp2[83] ));
  NOR2_X1    g254(.A1(new_n282_), .A2(new_n514_), .ZN(\selectp2[84] ));
  NOR2_X1    g255(.A1(new_n284_), .A2(new_n514_), .ZN(\selectp2[85] ));
  NOR2_X1    g256(.A1(new_n286_), .A2(new_n514_), .ZN(\selectp2[86] ));
  NOR2_X1    g257(.A1(new_n514_), .A2(new_n288_), .ZN(\selectp2[87] ));
  NOR2_X1    g258(.A1(new_n290_), .A2(new_n514_), .ZN(\selectp2[88] ));
  NOR2_X1    g259(.A1(new_n292_), .A2(new_n514_), .ZN(\selectp2[89] ));
  NOR2_X1    g260(.A1(new_n294_), .A2(new_n514_), .ZN(\selectp2[90] ));
  NOR2_X1    g261(.A1(new_n514_), .A2(new_n296_), .ZN(\selectp2[91] ));
  NOR2_X1    g262(.A1(new_n298_), .A2(new_n514_), .ZN(\selectp2[92] ));
  NOR2_X1    g263(.A1(new_n514_), .A2(new_n300_), .ZN(\selectp2[93] ));
  NOR2_X1    g264(.A1(new_n514_), .A2(new_n302_), .ZN(\selectp2[94] ));
  NOR2_X1    g265(.A1(new_n514_), .A2(new_n304_), .ZN(\selectp2[95] ));
  NAND4_X1   g266(.A1(new_n324_), .A2(new_n427_), .A3(\count[5] ), .A4(\count[6] ), .ZN(new_n531_));
  NOR2_X1    g267(.A1(new_n271_), .A2(new_n531_), .ZN(\selectp2[96] ));
  NOR2_X1    g268(.A1(new_n275_), .A2(new_n531_), .ZN(\selectp2[97] ));
  NOR2_X1    g269(.A1(new_n277_), .A2(new_n531_), .ZN(\selectp2[98] ));
  NOR2_X1    g270(.A1(new_n279_), .A2(new_n531_), .ZN(\selectp2[99] ));
  NOR2_X1    g271(.A1(new_n282_), .A2(new_n531_), .ZN(\selectp2[100] ));
  NOR2_X1    g272(.A1(new_n284_), .A2(new_n531_), .ZN(\selectp2[101] ));
  NOR2_X1    g273(.A1(new_n286_), .A2(new_n531_), .ZN(\selectp2[102] ));
  NOR2_X1    g274(.A1(new_n531_), .A2(new_n288_), .ZN(\selectp2[103] ));
  NOR2_X1    g275(.A1(new_n290_), .A2(new_n531_), .ZN(\selectp2[104] ));
  NOR2_X1    g276(.A1(new_n292_), .A2(new_n531_), .ZN(\selectp2[105] ));
  NOR2_X1    g277(.A1(new_n294_), .A2(new_n531_), .ZN(\selectp2[106] ));
  NOR2_X1    g278(.A1(new_n531_), .A2(new_n296_), .ZN(\selectp2[107] ));
  NOR2_X1    g279(.A1(new_n298_), .A2(new_n531_), .ZN(\selectp2[108] ));
  NOR2_X1    g280(.A1(new_n531_), .A2(new_n300_), .ZN(\selectp2[109] ));
  NOR2_X1    g281(.A1(new_n531_), .A2(new_n302_), .ZN(\selectp2[110] ));
  NOR2_X1    g282(.A1(new_n531_), .A2(new_n304_), .ZN(\selectp2[111] ));
  NAND4_X1   g283(.A1(new_n427_), .A2(\count[4] ), .A3(\count[5] ), .A4(\count[6] ), .ZN(new_n548_));
  NOR2_X1    g284(.A1(new_n271_), .A2(new_n548_), .ZN(\selectp2[112] ));
  NOR2_X1    g285(.A1(new_n275_), .A2(new_n548_), .ZN(\selectp2[113] ));
  NOR2_X1    g286(.A1(new_n277_), .A2(new_n548_), .ZN(\selectp2[114] ));
  NOR2_X1    g287(.A1(new_n279_), .A2(new_n548_), .ZN(\selectp2[115] ));
  NOR2_X1    g288(.A1(new_n282_), .A2(new_n548_), .ZN(\selectp2[116] ));
  NOR2_X1    g289(.A1(new_n284_), .A2(new_n548_), .ZN(\selectp2[117] ));
  NOR2_X1    g290(.A1(new_n286_), .A2(new_n548_), .ZN(\selectp2[118] ));
  NOR2_X1    g291(.A1(new_n288_), .A2(new_n548_), .ZN(\selectp2[119] ));
  NOR2_X1    g292(.A1(new_n290_), .A2(new_n548_), .ZN(\selectp2[120] ));
  NOR2_X1    g293(.A1(new_n292_), .A2(new_n548_), .ZN(\selectp2[121] ));
  NOR2_X1    g294(.A1(new_n294_), .A2(new_n548_), .ZN(\selectp2[122] ));
  NOR2_X1    g295(.A1(new_n296_), .A2(new_n548_), .ZN(\selectp2[123] ));
  NOR2_X1    g296(.A1(new_n298_), .A2(new_n548_), .ZN(\selectp2[124] ));
  NOR2_X1    g297(.A1(new_n300_), .A2(new_n548_), .ZN(\selectp2[125] ));
  NOR2_X1    g298(.A1(new_n302_), .A2(new_n548_), .ZN(\selectp2[126] ));
  NOR2_X1    g299(.A1(new_n548_), .A2(new_n304_), .ZN(\selectp2[127] ));
endmodule


