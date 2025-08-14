// Benchmark "ctrl" written by ABC on Mon Sep 11 23:27:38 2023

module ctrl ( 
    \opcode[0] , \opcode[1] , \opcode[2] , \opcode[3] , \opcode[4] ,
    \op_ext[0] , \op_ext[1] ,
    \sel_reg_dst[0] , \sel_reg_dst[1] , \sel_alu_opB[0] , \sel_alu_opB[1] ,
    \alu_op[0] , \alu_op[1] , \alu_op[2] , \alu_op_ext[0] ,
    \alu_op_ext[1] , \alu_op_ext[2] , \alu_op_ext[3] , halt, reg_write,
    sel_pc_opA, sel_pc_opB, beqz, bnez, bgez, bltz, jump, Cin, invA, invB,
    sign, mem_write, sel_wb  );
  input  \opcode[0] , \opcode[1] , \opcode[2] , \opcode[3] , \opcode[4] ,
    \op_ext[0] , \op_ext[1] ;
  output \sel_reg_dst[0] , \sel_reg_dst[1] , \sel_alu_opB[0] ,
    \sel_alu_opB[1] , \alu_op[0] , \alu_op[1] , \alu_op[2] ,
    \alu_op_ext[0] , \alu_op_ext[1] , \alu_op_ext[2] , \alu_op_ext[3] ,
    halt, reg_write, sel_pc_opA, sel_pc_opB, beqz, bnez, bgez, bltz, jump,
    Cin, invA, invB, sign, mem_write, sel_wb;
  wire new_n34_, new_n35_, new_n36_, new_n37_, new_n38_, new_n39_, new_n40_,
    new_n41_, new_n42_, new_n43_, new_n44_, new_n45_, new_n46_, new_n47_,
    new_n49_, new_n50_, new_n51_, new_n52_, new_n53_, new_n54_, new_n55_,
    new_n56_, new_n57_, new_n59_, new_n60_, new_n61_, new_n62_, new_n64_,
    new_n65_, new_n66_, new_n67_, new_n69_, new_n70_, new_n71_, new_n72_,
    new_n73_, new_n74_, new_n75_, new_n76_, new_n77_, new_n78_, new_n79_,
    new_n81_, new_n82_, new_n83_, new_n85_, new_n86_, new_n87_, new_n88_,
    new_n89_, new_n90_, new_n92_, new_n93_, new_n94_, new_n95_, new_n96_,
    new_n98_, new_n99_, new_n100_, new_n102_, new_n104_, new_n105_,
    new_n106_, new_n108_, new_n110_, new_n111_, new_n112_, new_n113_,
    new_n118_, new_n123_, new_n124_, new_n125_, new_n126_, new_n127_,
    new_n128_, new_n130_, new_n131_, new_n133_, new_n134_, new_n137_,
    new_n138_;
  INV_X1     g000(.I(\opcode[2] ), .ZN(new_n34_));
  INV_X1     g001(.I(\opcode[0] ), .ZN(new_n35_));
  NAND2_X1   g002(.A1(\opcode[3] ), .A2(\opcode[4] ), .ZN(new_n36_));
  NOR3_X1    g003(.A1(new_n36_), .A2(new_n35_), .A3(\opcode[1] ), .ZN(new_n37_));
  INV_X1     g004(.I(\opcode[1] ), .ZN(new_n38_));
  INV_X1     g005(.I(\opcode[3] ), .ZN(new_n39_));
  INV_X1     g006(.I(\opcode[4] ), .ZN(new_n40_));
  NOR3_X1    g007(.A1(new_n38_), .A2(new_n39_), .A3(new_n40_), .ZN(new_n41_));
  OAI21_X1   g008(.A1(new_n37_), .A2(new_n41_), .B(new_n34_), .ZN(new_n42_));
  NOR2_X1    g009(.A1(new_n39_), .A2(\opcode[1] ), .ZN(new_n43_));
  NOR2_X1    g010(.A1(\opcode[3] ), .A2(\opcode[4] ), .ZN(new_n44_));
  INV_X1     g011(.I(new_n44_), .ZN(new_n45_));
  NAND2_X1   g012(.A1(new_n45_), .A2(new_n36_), .ZN(new_n46_));
  AOI22_X1   g013(.A1(new_n46_), .A2(\opcode[1] ), .B1(\opcode[4] ), .B2(new_n43_), .ZN(new_n47_));
  OAI21_X1   g014(.A1(new_n47_), .A2(new_n34_), .B(new_n42_), .ZN(\sel_reg_dst[0] ));
  INV_X1     g015(.I(new_n36_), .ZN(new_n49_));
  AOI21_X1   g016(.A1(new_n49_), .A2(new_n35_), .B(\opcode[1] ), .ZN(new_n50_));
  INV_X1     g017(.I(new_n50_), .ZN(new_n51_));
  NOR2_X1    g018(.A1(new_n40_), .A2(\opcode[3] ), .ZN(new_n52_));
  INV_X1     g019(.I(new_n52_), .ZN(new_n53_));
  NAND2_X1   g020(.A1(new_n53_), .A2(\opcode[1] ), .ZN(new_n54_));
  NAND2_X1   g021(.A1(new_n51_), .A2(new_n54_), .ZN(new_n55_));
  NOR2_X1    g022(.A1(\opcode[3] ), .A2(\opcode[4] ), .ZN(new_n56_));
  AOI21_X1   g023(.A1(new_n56_), .A2(\opcode[1] ), .B(new_n34_), .ZN(new_n57_));
  AOI21_X1   g024(.A1(new_n55_), .A2(new_n34_), .B(new_n57_), .ZN(\sel_reg_dst[1] ));
  NAND2_X1   g025(.A1(new_n46_), .A2(new_n35_), .ZN(new_n59_));
  NAND2_X1   g026(.A1(new_n40_), .A2(\opcode[3] ), .ZN(new_n60_));
  NAND2_X1   g027(.A1(new_n60_), .A2(\opcode[0] ), .ZN(new_n61_));
  AOI21_X1   g028(.A1(new_n59_), .A2(new_n61_), .B(new_n38_), .ZN(new_n62_));
  NOR3_X1    g029(.A1(new_n62_), .A2(\opcode[2] ), .A3(new_n50_), .ZN(\sel_alu_opB[0] ));
  NOR3_X1    g030(.A1(\opcode[0] ), .A2(\opcode[3] ), .A3(\opcode[4] ), .ZN(new_n64_));
  AOI21_X1   g031(.A1(new_n46_), .A2(\opcode[0] ), .B(new_n64_), .ZN(new_n65_));
  OAI21_X1   g032(.A1(new_n65_), .A2(\opcode[1] ), .B(new_n54_), .ZN(new_n66_));
  NOR2_X1    g033(.A1(new_n52_), .A2(new_n34_), .ZN(new_n67_));
  AOI21_X1   g034(.A1(new_n66_), .A2(new_n34_), .B(new_n67_), .ZN(\sel_alu_opB[1] ));
  INV_X1     g035(.I(\op_ext[0] ), .ZN(new_n69_));
  NOR4_X1    g036(.A1(new_n39_), .A2(new_n40_), .A3(new_n69_), .A4(\opcode[0] ), .ZN(new_n70_));
  INV_X1     g037(.I(\op_ext[1] ), .ZN(new_n71_));
  NAND3_X1   g038(.A1(new_n40_), .A2(new_n71_), .A3(\opcode[3] ), .ZN(new_n72_));
  NOR3_X1    g039(.A1(new_n39_), .A2(\opcode[4] ), .A3(\op_ext[0] ), .ZN(new_n73_));
  AND2_X2    g040(.A1(\opcode[3] ), .A2(\op_ext[0] ), .Z(new_n74_));
  OAI21_X1   g041(.A1(new_n73_), .A2(new_n74_), .B(\op_ext[1] ), .ZN(new_n75_));
  AOI21_X1   g042(.A1(new_n75_), .A2(new_n72_), .B(new_n35_), .ZN(new_n76_));
  OAI21_X1   g043(.A1(new_n76_), .A2(new_n70_), .B(\opcode[1] ), .ZN(new_n77_));
  NOR2_X1    g044(.A1(new_n53_), .A2(new_n35_), .ZN(new_n78_));
  NOR2_X1    g045(.A1(new_n78_), .A2(new_n34_), .ZN(new_n79_));
  AOI21_X1   g046(.A1(new_n77_), .A2(new_n34_), .B(new_n79_), .ZN(\alu_op[0] ));
  AOI21_X1   g047(.A1(\opcode[4] ), .A2(new_n71_), .B(new_n39_), .ZN(new_n81_));
  AOI21_X1   g048(.A1(new_n81_), .A2(\opcode[1] ), .B(\opcode[2] ), .ZN(new_n82_));
  AOI21_X1   g049(.A1(new_n52_), .A2(\opcode[1] ), .B(new_n34_), .ZN(new_n83_));
  NOR2_X1    g050(.A1(new_n82_), .A2(new_n83_), .ZN(\alu_op[1] ));
  NAND2_X1   g051(.A1(\opcode[2] ), .A2(\opcode[3] ), .ZN(new_n85_));
  NAND2_X1   g052(.A1(new_n36_), .A2(new_n38_), .ZN(new_n86_));
  NOR2_X1    g053(.A1(new_n86_), .A2(new_n44_), .ZN(new_n87_));
  NAND2_X1   g054(.A1(new_n36_), .A2(new_n35_), .ZN(new_n88_));
  OAI22_X1   g055(.A1(new_n88_), .A2(new_n44_), .B1(new_n35_), .B2(new_n56_), .ZN(new_n89_));
  AOI21_X1   g056(.A1(new_n89_), .A2(\opcode[1] ), .B(new_n87_), .ZN(new_n90_));
  OAI22_X1   g057(.A1(new_n90_), .A2(\opcode[2] ), .B1(new_n40_), .B2(new_n85_), .ZN(\alu_op[2] ));
  NAND2_X1   g058(.A1(new_n38_), .A2(new_n34_), .ZN(new_n92_));
  NOR2_X1    g059(.A1(new_n49_), .A2(new_n44_), .ZN(new_n93_));
  INV_X1     g060(.I(new_n64_), .ZN(new_n94_));
  OAI21_X1   g061(.A1(new_n93_), .A2(new_n35_), .B(new_n94_), .ZN(new_n95_));
  AOI21_X1   g062(.A1(new_n95_), .A2(\opcode[1] ), .B(new_n37_), .ZN(new_n96_));
  OAI22_X1   g063(.A1(new_n96_), .A2(new_n34_), .B1(new_n50_), .B2(new_n92_), .ZN(\alu_op_ext[0] ));
  OAI21_X1   g064(.A1(new_n53_), .A2(\opcode[0] ), .B(\opcode[1] ), .ZN(new_n98_));
  NAND3_X1   g065(.A1(new_n98_), .A2(\opcode[1] ), .A3(new_n34_), .ZN(new_n99_));
  NAND3_X1   g066(.A1(new_n46_), .A2(\opcode[1] ), .A3(\opcode[2] ), .ZN(new_n100_));
  NAND2_X1   g067(.A1(new_n99_), .A2(new_n100_), .ZN(\alu_op_ext[1] ));
  NAND2_X1   g068(.A1(new_n98_), .A2(new_n86_), .ZN(new_n102_));
  AOI21_X1   g069(.A1(new_n102_), .A2(new_n34_), .B(new_n57_), .ZN(\alu_op_ext[2] ));
  AOI21_X1   g070(.A1(\opcode[0] ), .A2(\opcode[4] ), .B(\opcode[3] ), .ZN(new_n104_));
  OR2_X2     g071(.A1(new_n104_), .A2(new_n38_), .Z(new_n105_));
  NOR2_X1    g072(.A1(new_n87_), .A2(\opcode[2] ), .ZN(new_n106_));
  AOI21_X1   g073(.A1(new_n106_), .A2(new_n105_), .B(new_n67_), .ZN(\alu_op_ext[3] ));
  INV_X1     g074(.I(new_n56_), .ZN(new_n108_));
  NOR4_X1    g075(.A1(new_n108_), .A2(\opcode[0] ), .A3(\opcode[1] ), .A4(\opcode[2] ), .ZN(halt));
  NOR2_X1    g076(.A1(new_n56_), .A2(new_n38_), .ZN(new_n110_));
  NOR2_X1    g077(.A1(new_n104_), .A2(\opcode[1] ), .ZN(new_n111_));
  OAI21_X1   g078(.A1(new_n111_), .A2(new_n110_), .B(new_n34_), .ZN(new_n112_));
  AOI21_X1   g079(.A1(new_n39_), .A2(\opcode[1] ), .B(\opcode[4] ), .ZN(new_n113_));
  OAI21_X1   g080(.A1(new_n34_), .A2(new_n113_), .B(new_n112_), .ZN(reg_write));
  NOR3_X1    g081(.A1(new_n108_), .A2(new_n35_), .A3(new_n34_), .ZN(sel_pc_opA));
  NOR3_X1    g082(.A1(new_n108_), .A2(\opcode[0] ), .A3(new_n34_), .ZN(sel_pc_opB));
  NOR4_X1    g083(.A1(new_n60_), .A2(\opcode[0] ), .A3(\opcode[1] ), .A4(new_n34_), .ZN(beqz));
  AOI21_X1   g084(.A1(new_n61_), .A2(\opcode[0] ), .B(\opcode[1] ), .ZN(new_n118_));
  NOR3_X1    g085(.A1(new_n118_), .A2(\opcode[1] ), .A3(new_n34_), .ZN(bnez));
  NOR4_X1    g086(.A1(new_n60_), .A2(new_n35_), .A3(new_n38_), .A4(new_n34_), .ZN(bgez));
  NOR4_X1    g087(.A1(new_n60_), .A2(\opcode[0] ), .A3(new_n38_), .A4(new_n34_), .ZN(bltz));
  NOR2_X1    g088(.A1(new_n108_), .A2(new_n34_), .ZN(jump));
  AOI21_X1   g089(.A1(\opcode[0] ), .A2(\opcode[1] ), .B(new_n36_), .ZN(new_n123_));
  NOR2_X1    g090(.A1(new_n123_), .A2(new_n34_), .ZN(new_n124_));
  NOR2_X1    g091(.A1(new_n35_), .A2(new_n38_), .ZN(new_n125_));
  OAI21_X1   g092(.A1(new_n73_), .A2(new_n74_), .B(new_n125_), .ZN(new_n126_));
  NOR2_X1    g093(.A1(new_n35_), .A2(\opcode[1] ), .ZN(new_n127_));
  AOI21_X1   g094(.A1(new_n61_), .A2(new_n127_), .B(\opcode[2] ), .ZN(new_n128_));
  AOI21_X1   g095(.A1(new_n128_), .A2(new_n126_), .B(new_n124_), .ZN(Cin));
  NOR4_X1    g096(.A1(new_n36_), .A2(new_n35_), .A3(new_n69_), .A4(\op_ext[1] ), .ZN(new_n130_));
  NOR2_X1    g097(.A1(new_n130_), .A2(new_n38_), .ZN(new_n131_));
  NOR3_X1    g098(.A1(new_n118_), .A2(\opcode[2] ), .A3(new_n131_), .ZN(invA));
  NAND2_X1   g099(.A1(new_n75_), .A2(new_n72_), .ZN(new_n133_));
  NAND2_X1   g100(.A1(new_n133_), .A2(new_n125_), .ZN(new_n134_));
  AOI21_X1   g101(.A1(new_n134_), .A2(new_n34_), .B(new_n124_), .ZN(invB));
  AOI21_X1   g102(.A1(new_n52_), .A2(new_n35_), .B(\opcode[1] ), .ZN(new_n137_));
  NOR2_X1    g103(.A1(new_n78_), .A2(new_n38_), .ZN(new_n138_));
  NOR3_X1    g104(.A1(new_n138_), .A2(\opcode[2] ), .A3(new_n137_), .ZN(mem_write));
  NOR4_X1    g105(.A1(new_n53_), .A2(new_n35_), .A3(\opcode[1] ), .A4(\opcode[2] ), .ZN(sel_wb));
  assign     sign = 1'b1;
endmodule


