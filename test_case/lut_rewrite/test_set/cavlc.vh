// Benchmark "cavlc" written by ABC on Mon Sep 11 23:26:46 2023

module cavlc ( 
    \totalcoeffs[0] , \totalcoeffs[1] , \totalcoeffs[2] , \totalcoeffs[3] ,
    \totalcoeffs[4] , \ctable[0] , \ctable[1] , \ctable[2] ,
    \trailingones[0] , \trailingones[1] ,
    \coeff_token[0] , \coeff_token[1] , \coeff_token[2] , \coeff_token[3] ,
    \coeff_token[4] , \coeff_token[5] , \ctoken_len[0] , \ctoken_len[1] ,
    \ctoken_len[2] , \ctoken_len[3] , \ctoken_len[4]   );
  input  \totalcoeffs[0] , \totalcoeffs[1] , \totalcoeffs[2] ,
    \totalcoeffs[3] , \totalcoeffs[4] , \ctable[0] , \ctable[1] ,
    \ctable[2] , \trailingones[0] , \trailingones[1] ;
  output \coeff_token[0] , \coeff_token[1] , \coeff_token[2] ,
    \coeff_token[3] , \coeff_token[4] , \coeff_token[5] , \ctoken_len[0] ,
    \ctoken_len[1] , \ctoken_len[2] , \ctoken_len[3] , \ctoken_len[4] ;
  wire new_n22_, new_n23_, new_n24_, new_n25_, new_n26_, new_n27_, new_n28_,
    new_n29_, new_n30_, new_n31_, new_n32_, new_n33_, new_n34_, new_n35_,
    new_n36_, new_n37_, new_n38_, new_n39_, new_n40_, new_n41_, new_n42_,
    new_n43_, new_n44_, new_n45_, new_n46_, new_n47_, new_n48_, new_n49_,
    new_n50_, new_n51_, new_n52_, new_n53_, new_n54_, new_n55_, new_n56_,
    new_n57_, new_n58_, new_n59_, new_n60_, new_n61_, new_n62_, new_n63_,
    new_n64_, new_n65_, new_n66_, new_n67_, new_n68_, new_n69_, new_n70_,
    new_n71_, new_n72_, new_n73_, new_n74_, new_n75_, new_n76_, new_n77_,
    new_n78_, new_n79_, new_n80_, new_n81_, new_n82_, new_n83_, new_n84_,
    new_n85_, new_n86_, new_n87_, new_n88_, new_n89_, new_n90_, new_n91_,
    new_n92_, new_n93_, new_n94_, new_n95_, new_n96_, new_n97_, new_n98_,
    new_n99_, new_n100_, new_n101_, new_n102_, new_n103_, new_n104_,
    new_n105_, new_n106_, new_n107_, new_n108_, new_n109_, new_n110_,
    new_n111_, new_n112_, new_n113_, new_n114_, new_n115_, new_n116_,
    new_n118_, new_n119_, new_n120_, new_n121_, new_n122_, new_n123_,
    new_n124_, new_n125_, new_n126_, new_n127_, new_n128_, new_n129_,
    new_n130_, new_n131_, new_n132_, new_n133_, new_n134_, new_n135_,
    new_n136_, new_n137_, new_n138_, new_n139_, new_n140_, new_n141_,
    new_n142_, new_n143_, new_n144_, new_n145_, new_n146_, new_n147_,
    new_n148_, new_n149_, new_n150_, new_n151_, new_n152_, new_n153_,
    new_n154_, new_n155_, new_n156_, new_n157_, new_n158_, new_n159_,
    new_n160_, new_n161_, new_n162_, new_n163_, new_n164_, new_n165_,
    new_n166_, new_n167_, new_n168_, new_n169_, new_n170_, new_n171_,
    new_n172_, new_n173_, new_n174_, new_n175_, new_n176_, new_n177_,
    new_n178_, new_n179_, new_n180_, new_n181_, new_n182_, new_n183_,
    new_n184_, new_n185_, new_n186_, new_n187_, new_n188_, new_n189_,
    new_n190_, new_n191_, new_n192_, new_n193_, new_n195_, new_n196_,
    new_n197_, new_n198_, new_n199_, new_n200_, new_n201_, new_n202_,
    new_n203_, new_n204_, new_n205_, new_n206_, new_n207_, new_n208_,
    new_n209_, new_n210_, new_n211_, new_n212_, new_n213_, new_n214_,
    new_n215_, new_n216_, new_n217_, new_n218_, new_n219_, new_n220_,
    new_n221_, new_n222_, new_n223_, new_n224_, new_n225_, new_n226_,
    new_n227_, new_n228_, new_n229_, new_n230_, new_n231_, new_n232_,
    new_n233_, new_n234_, new_n235_, new_n236_, new_n237_, new_n238_,
    new_n239_, new_n240_, new_n241_, new_n242_, new_n243_, new_n244_,
    new_n245_, new_n246_, new_n247_, new_n248_, new_n249_, new_n250_,
    new_n251_, new_n252_, new_n253_, new_n254_, new_n255_, new_n256_,
    new_n257_, new_n259_, new_n260_, new_n261_, new_n262_, new_n263_,
    new_n264_, new_n265_, new_n266_, new_n267_, new_n268_, new_n269_,
    new_n270_, new_n271_, new_n272_, new_n273_, new_n274_, new_n275_,
    new_n276_, new_n277_, new_n278_, new_n279_, new_n280_, new_n281_,
    new_n282_, new_n283_, new_n284_, new_n285_, new_n286_, new_n287_,
    new_n288_, new_n289_, new_n290_, new_n291_, new_n292_, new_n293_,
    new_n294_, new_n295_, new_n296_, new_n297_, new_n298_, new_n299_,
    new_n300_, new_n301_, new_n302_, new_n303_, new_n304_, new_n305_,
    new_n306_, new_n308_, new_n309_, new_n310_, new_n311_, new_n312_,
    new_n314_, new_n315_, new_n316_, new_n318_, new_n319_, new_n320_,
    new_n321_, new_n322_, new_n323_, new_n324_, new_n325_, new_n326_,
    new_n327_, new_n328_, new_n329_, new_n330_, new_n331_, new_n332_,
    new_n333_, new_n334_, new_n335_, new_n336_, new_n337_, new_n338_,
    new_n339_, new_n340_, new_n341_, new_n342_, new_n343_, new_n344_,
    new_n345_, new_n346_, new_n347_, new_n348_, new_n349_, new_n350_,
    new_n351_, new_n352_, new_n353_, new_n354_, new_n355_, new_n356_,
    new_n357_, new_n358_, new_n359_, new_n360_, new_n361_, new_n362_,
    new_n363_, new_n364_, new_n365_, new_n367_, new_n368_, new_n369_,
    new_n370_, new_n371_, new_n372_, new_n373_, new_n374_, new_n375_,
    new_n376_, new_n377_, new_n378_, new_n379_, new_n380_, new_n381_,
    new_n382_, new_n383_, new_n384_, new_n385_, new_n386_, new_n387_,
    new_n388_, new_n389_, new_n390_, new_n391_, new_n392_, new_n393_,
    new_n394_, new_n395_, new_n396_, new_n397_, new_n398_, new_n399_,
    new_n400_, new_n401_, new_n402_, new_n403_, new_n404_, new_n405_,
    new_n406_, new_n407_, new_n408_, new_n409_, new_n410_, new_n411_,
    new_n412_, new_n413_, new_n414_, new_n415_, new_n416_, new_n417_,
    new_n418_, new_n419_, new_n420_, new_n421_, new_n423_, new_n424_,
    new_n425_, new_n426_, new_n427_, new_n428_, new_n429_, new_n430_,
    new_n431_, new_n432_, new_n433_, new_n434_, new_n435_, new_n436_,
    new_n437_, new_n438_, new_n439_, new_n440_, new_n441_, new_n442_,
    new_n443_, new_n444_, new_n445_, new_n446_, new_n447_, new_n448_,
    new_n449_, new_n450_, new_n451_, new_n452_, new_n453_, new_n454_,
    new_n455_, new_n456_, new_n457_, new_n458_, new_n459_, new_n460_,
    new_n462_, new_n463_, new_n464_, new_n465_, new_n466_, new_n467_,
    new_n468_, new_n469_, new_n470_, new_n471_, new_n472_, new_n473_,
    new_n474_, new_n475_, new_n476_, new_n477_, new_n478_, new_n479_,
    new_n480_, new_n481_, new_n482_, new_n483_, new_n484_, new_n485_,
    new_n487_, new_n488_, new_n489_, new_n490_, new_n491_;
  INV_X1     g000(.I(\trailingones[1] ), .ZN(new_n22_));
  NAND2_X1   g001(.A1(new_n22_), .A2(\ctable[1] ), .ZN(new_n23_));
  NAND2_X1   g002(.A1(\totalcoeffs[4] ), .A2(\trailingones[1] ), .ZN(new_n24_));
  INV_X1     g003(.I(\trailingones[0] ), .ZN(new_n25_));
  INV_X1     g004(.I(\ctable[0] ), .ZN(new_n26_));
  INV_X1     g005(.I(\ctable[1] ), .ZN(new_n27_));
  NOR2_X1    g006(.A1(new_n26_), .A2(new_n27_), .ZN(new_n28_));
  INV_X1     g007(.I(new_n28_), .ZN(new_n29_));
  NAND2_X1   g008(.A1(new_n29_), .A2(new_n25_), .ZN(new_n30_));
  AOI21_X1   g009(.A1(new_n23_), .A2(new_n24_), .B(new_n30_), .ZN(new_n31_));
  NOR2_X1    g010(.A1(\trailingones[0] ), .A2(\trailingones[1] ), .ZN(new_n32_));
  NAND2_X1   g011(.A1(new_n32_), .A2(new_n27_), .ZN(new_n33_));
  INV_X1     g012(.I(\totalcoeffs[4] ), .ZN(new_n34_));
  NOR2_X1    g013(.A1(new_n34_), .A2(new_n25_), .ZN(new_n35_));
  NAND2_X1   g014(.A1(new_n35_), .A2(\ctable[1] ), .ZN(new_n36_));
  AOI21_X1   g015(.A1(new_n36_), .A2(new_n33_), .B(new_n26_), .ZN(new_n37_));
  INV_X1     g016(.I(\totalcoeffs[2] ), .ZN(new_n38_));
  NOR2_X1    g017(.A1(\totalcoeffs[1] ), .A2(\totalcoeffs[3] ), .ZN(new_n39_));
  NAND2_X1   g018(.A1(new_n39_), .A2(new_n38_), .ZN(new_n40_));
  NOR3_X1    g019(.A1(new_n40_), .A2(\totalcoeffs[0] ), .A3(\ctable[2] ), .ZN(new_n41_));
  OAI21_X1   g020(.A1(new_n31_), .A2(new_n37_), .B(new_n41_), .ZN(new_n42_));
  INV_X1     g021(.I(\ctable[2] ), .ZN(new_n43_));
  NAND2_X1   g022(.A1(\ctable[2] ), .A2(\trailingones[0] ), .ZN(new_n44_));
  NOR2_X1    g023(.A1(\totalcoeffs[0] ), .A2(\totalcoeffs[1] ), .ZN(new_n45_));
  INV_X1     g024(.I(new_n45_), .ZN(new_n46_));
  NAND2_X1   g025(.A1(new_n22_), .A2(\totalcoeffs[2] ), .ZN(new_n47_));
  NOR4_X1    g026(.A1(new_n46_), .A2(new_n47_), .A3(\ctable[0] ), .A4(new_n44_), .ZN(new_n48_));
  OAI22_X1   g027(.A1(new_n44_), .A2(\ctable[0] ), .B1(new_n22_), .B2(\ctable[2] ), .ZN(new_n49_));
  NAND2_X1   g028(.A1(new_n49_), .A2(\totalcoeffs[1] ), .ZN(new_n50_));
  INV_X1     g029(.I(\totalcoeffs[1] ), .ZN(new_n51_));
  NOR2_X1    g030(.A1(\ctable[0] ), .A2(\trailingones[1] ), .ZN(new_n52_));
  OAI21_X1   g031(.A1(new_n51_), .A2(\ctable[2] ), .B(new_n52_), .ZN(new_n53_));
  NAND2_X1   g032(.A1(new_n38_), .A2(\totalcoeffs[0] ), .ZN(new_n54_));
  AOI21_X1   g033(.A1(new_n50_), .A2(new_n53_), .B(new_n54_), .ZN(new_n55_));
  NOR2_X1    g034(.A1(new_n55_), .A2(new_n48_), .ZN(new_n56_));
  NOR2_X1    g035(.A1(\totalcoeffs[2] ), .A2(\totalcoeffs[3] ), .ZN(new_n57_));
  NAND2_X1   g036(.A1(\totalcoeffs[0] ), .A2(\totalcoeffs[3] ), .ZN(new_n58_));
  OAI21_X1   g037(.A1(new_n22_), .A2(new_n57_), .B(new_n58_), .ZN(new_n59_));
  NAND2_X1   g038(.A1(new_n59_), .A2(new_n51_), .ZN(new_n60_));
  INV_X1     g039(.I(\totalcoeffs[3] ), .ZN(new_n61_));
  NOR2_X1    g040(.A1(\totalcoeffs[2] ), .A2(\ctable[0] ), .ZN(new_n62_));
  NAND2_X1   g041(.A1(\totalcoeffs[1] ), .A2(\totalcoeffs[2] ), .ZN(new_n63_));
  OAI21_X1   g042(.A1(\totalcoeffs[0] ), .A2(new_n62_), .B(new_n63_), .ZN(new_n64_));
  AOI22_X1   g043(.A1(new_n64_), .A2(new_n22_), .B1(\totalcoeffs[1] ), .B2(new_n61_), .ZN(new_n65_));
  AOI21_X1   g044(.A1(new_n65_), .A2(new_n60_), .B(\ctable[2] ), .ZN(new_n66_));
  INV_X1     g045(.I(\totalcoeffs[0] ), .ZN(new_n67_));
  NAND2_X1   g046(.A1(new_n67_), .A2(\trailingones[1] ), .ZN(new_n68_));
  NAND2_X1   g047(.A1(new_n68_), .A2(\totalcoeffs[1] ), .ZN(new_n69_));
  NOR2_X1    g048(.A1(\totalcoeffs[3] ), .A2(\ctable[0] ), .ZN(new_n70_));
  INV_X1     g049(.I(new_n70_), .ZN(new_n71_));
  NOR2_X1    g050(.A1(new_n22_), .A2(\totalcoeffs[1] ), .ZN(new_n72_));
  NOR2_X1    g051(.A1(new_n71_), .A2(new_n72_), .ZN(new_n73_));
  NAND2_X1   g052(.A1(new_n73_), .A2(new_n69_), .ZN(new_n74_));
  NOR2_X1    g053(.A1(new_n67_), .A2(\trailingones[1] ), .ZN(new_n75_));
  NOR2_X1    g054(.A1(new_n51_), .A2(\trailingones[1] ), .ZN(new_n76_));
  NOR2_X1    g055(.A1(new_n76_), .A2(\ctable[2] ), .ZN(new_n77_));
  OAI21_X1   g056(.A1(\totalcoeffs[1] ), .A2(new_n75_), .B(new_n77_), .ZN(new_n78_));
  AOI21_X1   g057(.A1(new_n78_), .A2(new_n74_), .B(\totalcoeffs[2] ), .ZN(new_n79_));
  NOR2_X1    g058(.A1(new_n79_), .A2(new_n66_), .ZN(new_n80_));
  OAI22_X1   g059(.A1(new_n80_), .A2(\trailingones[0] ), .B1(\totalcoeffs[3] ), .B2(new_n56_), .ZN(new_n81_));
  NOR2_X1    g060(.A1(new_n67_), .A2(new_n22_), .ZN(new_n82_));
  NOR2_X1    g061(.A1(\totalcoeffs[0] ), .A2(\trailingones[1] ), .ZN(new_n83_));
  NOR2_X1    g062(.A1(new_n82_), .A2(new_n83_), .ZN(new_n84_));
  NOR2_X1    g063(.A1(new_n84_), .A2(new_n51_), .ZN(new_n85_));
  NAND3_X1   g064(.A1(new_n85_), .A2(\totalcoeffs[2] ), .A3(\ctable[0] ), .ZN(new_n86_));
  NOR4_X1    g065(.A1(new_n22_), .A2(\totalcoeffs[0] ), .A3(\totalcoeffs[1] ), .A4(\totalcoeffs[2] ), .ZN(new_n87_));
  OAI21_X1   g066(.A1(new_n87_), .A2(\ctable[0] ), .B(\ctable[1] ), .ZN(new_n88_));
  AOI21_X1   g067(.A1(new_n86_), .A2(new_n88_), .B(new_n25_), .ZN(new_n89_));
  NAND3_X1   g068(.A1(new_n75_), .A2(new_n51_), .A3(\totalcoeffs[2] ), .ZN(new_n90_));
  NAND2_X1   g069(.A1(new_n68_), .A2(new_n51_), .ZN(new_n91_));
  NAND2_X1   g070(.A1(new_n91_), .A2(new_n25_), .ZN(new_n92_));
  AOI21_X1   g071(.A1(new_n92_), .A2(new_n90_), .B(\ctable[0] ), .ZN(new_n93_));
  OAI21_X1   g072(.A1(new_n89_), .A2(new_n93_), .B(\totalcoeffs[3] ), .ZN(new_n94_));
  NAND2_X1   g073(.A1(\totalcoeffs[2] ), .A2(\trailingones[1] ), .ZN(new_n95_));
  INV_X1     g074(.I(new_n95_), .ZN(new_n96_));
  INV_X1     g075(.I(new_n76_), .ZN(new_n97_));
  NOR2_X1    g076(.A1(new_n97_), .A2(\totalcoeffs[2] ), .ZN(new_n98_));
  NOR2_X1    g077(.A1(new_n98_), .A2(new_n96_), .ZN(new_n99_));
  NOR4_X1    g078(.A1(new_n99_), .A2(\totalcoeffs[0] ), .A3(\totalcoeffs[3] ), .A4(new_n27_), .ZN(new_n100_));
  OAI21_X1   g079(.A1(new_n75_), .A2(\totalcoeffs[2] ), .B(\ctable[1] ), .ZN(new_n101_));
  NAND2_X1   g080(.A1(new_n85_), .A2(new_n57_), .ZN(new_n102_));
  AOI21_X1   g081(.A1(new_n102_), .A2(new_n101_), .B(new_n26_), .ZN(new_n103_));
  OAI21_X1   g082(.A1(new_n103_), .A2(new_n100_), .B(\trailingones[0] ), .ZN(new_n104_));
  INV_X1     g083(.I(new_n57_), .ZN(new_n105_));
  NOR2_X1    g084(.A1(\totalcoeffs[1] ), .A2(\trailingones[1] ), .ZN(new_n106_));
  NAND2_X1   g085(.A1(new_n106_), .A2(new_n25_), .ZN(new_n107_));
  NOR3_X1    g086(.A1(new_n107_), .A2(new_n105_), .A3(\totalcoeffs[0] ), .ZN(new_n108_));
  NOR2_X1    g087(.A1(new_n38_), .A2(\totalcoeffs[3] ), .ZN(new_n109_));
  AOI22_X1   g088(.A1(new_n72_), .A2(new_n109_), .B1(\totalcoeffs[1] ), .B2(new_n25_), .ZN(new_n110_));
  OAI21_X1   g089(.A1(new_n27_), .A2(\totalcoeffs[2] ), .B(\totalcoeffs[3] ), .ZN(new_n111_));
  AOI21_X1   g090(.A1(new_n106_), .A2(new_n111_), .B(new_n96_), .ZN(new_n112_));
  OAI22_X1   g091(.A1(new_n112_), .A2(\trailingones[0] ), .B1(new_n110_), .B2(\totalcoeffs[0] ), .ZN(new_n113_));
  AOI21_X1   g092(.A1(new_n113_), .A2(new_n26_), .B(new_n108_), .ZN(new_n114_));
  NAND3_X1   g093(.A1(new_n94_), .A2(new_n104_), .A3(new_n114_), .ZN(new_n115_));
  AOI22_X1   g094(.A1(new_n115_), .A2(new_n43_), .B1(new_n27_), .B2(new_n81_), .ZN(new_n116_));
  OAI21_X1   g095(.A1(new_n116_), .A2(\totalcoeffs[4] ), .B(new_n42_), .ZN(\coeff_token[0] ));
  NOR2_X1    g096(.A1(new_n25_), .A2(\totalcoeffs[2] ), .ZN(new_n118_));
  INV_X1     g097(.I(new_n75_), .ZN(new_n119_));
  NAND2_X1   g098(.A1(\totalcoeffs[0] ), .A2(\totalcoeffs[1] ), .ZN(new_n120_));
  NAND3_X1   g099(.A1(new_n119_), .A2(new_n38_), .A3(new_n120_), .ZN(new_n121_));
  AOI21_X1   g100(.A1(new_n46_), .A2(\totalcoeffs[2] ), .B(\trailingones[0] ), .ZN(new_n122_));
  AOI22_X1   g101(.A1(new_n121_), .A2(new_n122_), .B1(new_n76_), .B2(new_n118_), .ZN(new_n123_));
  OAI22_X1   g102(.A1(new_n123_), .A2(new_n43_), .B1(new_n46_), .B2(new_n47_), .ZN(new_n124_));
  NAND4_X1   g103(.A1(new_n124_), .A2(new_n34_), .A3(new_n27_), .A4(new_n70_), .ZN(new_n125_));
  NAND2_X1   g104(.A1(\ctable[1] ), .A2(\trailingones[1] ), .ZN(new_n126_));
  INV_X1     g105(.I(new_n126_), .ZN(new_n127_));
  NOR2_X1    g106(.A1(new_n25_), .A2(\ctable[0] ), .ZN(new_n128_));
  NOR2_X1    g107(.A1(new_n127_), .A2(new_n128_), .ZN(new_n129_));
  NOR2_X1    g108(.A1(new_n129_), .A2(\totalcoeffs[0] ), .ZN(new_n130_));
  NAND2_X1   g109(.A1(new_n52_), .A2(new_n25_), .ZN(new_n131_));
  OAI21_X1   g110(.A1(new_n25_), .A2(new_n126_), .B(new_n131_), .ZN(new_n132_));
  OAI21_X1   g111(.A1(new_n130_), .A2(new_n132_), .B(\totalcoeffs[2] ), .ZN(new_n133_));
  INV_X1     g112(.I(new_n83_), .ZN(new_n134_));
  NAND2_X1   g113(.A1(\totalcoeffs[0] ), .A2(\trailingones[0] ), .ZN(new_n135_));
  NAND2_X1   g114(.A1(new_n38_), .A2(new_n25_), .ZN(new_n136_));
  OAI22_X1   g115(.A1(new_n134_), .A2(new_n136_), .B1(new_n95_), .B2(new_n135_), .ZN(new_n137_));
  NAND2_X1   g116(.A1(new_n137_), .A2(\ctable[0] ), .ZN(new_n138_));
  AOI21_X1   g117(.A1(new_n133_), .A2(new_n138_), .B(\totalcoeffs[4] ), .ZN(new_n139_));
  NOR2_X1    g118(.A1(new_n26_), .A2(\trailingones[0] ), .ZN(new_n140_));
  OAI21_X1   g119(.A1(new_n35_), .A2(new_n140_), .B(new_n27_), .ZN(new_n141_));
  NAND2_X1   g120(.A1(new_n27_), .A2(\trailingones[1] ), .ZN(new_n142_));
  NAND3_X1   g121(.A1(new_n142_), .A2(new_n67_), .A3(new_n38_), .ZN(new_n143_));
  AOI21_X1   g122(.A1(new_n141_), .A2(new_n24_), .B(new_n143_), .ZN(new_n144_));
  OAI21_X1   g123(.A1(new_n139_), .A2(new_n144_), .B(new_n51_), .ZN(new_n145_));
  NOR3_X1    g124(.A1(new_n47_), .A2(\ctable[1] ), .A3(new_n25_), .ZN(new_n146_));
  NAND2_X1   g125(.A1(new_n25_), .A2(\trailingones[1] ), .ZN(new_n147_));
  NAND2_X1   g126(.A1(new_n67_), .A2(\ctable[0] ), .ZN(new_n148_));
  NOR2_X1    g127(.A1(new_n147_), .A2(new_n148_), .ZN(new_n149_));
  NOR2_X1    g128(.A1(new_n27_), .A2(new_n25_), .ZN(new_n150_));
  NOR3_X1    g129(.A1(new_n129_), .A2(new_n67_), .A3(new_n150_), .ZN(new_n151_));
  OAI21_X1   g130(.A1(new_n151_), .A2(new_n149_), .B(new_n38_), .ZN(new_n152_));
  NOR2_X1    g131(.A1(\ctable[1] ), .A2(\trailingones[0] ), .ZN(new_n153_));
  AOI21_X1   g132(.A1(new_n67_), .A2(\ctable[1] ), .B(\totalcoeffs[2] ), .ZN(new_n154_));
  NOR3_X1    g133(.A1(new_n154_), .A2(\ctable[0] ), .A3(new_n25_), .ZN(new_n155_));
  OAI21_X1   g134(.A1(new_n155_), .A2(new_n153_), .B(new_n22_), .ZN(new_n156_));
  AOI21_X1   g135(.A1(new_n152_), .A2(new_n156_), .B(new_n51_), .ZN(new_n157_));
  OAI21_X1   g136(.A1(new_n157_), .A2(new_n146_), .B(new_n34_), .ZN(new_n158_));
  AOI21_X1   g137(.A1(new_n158_), .A2(new_n145_), .B(\totalcoeffs[3] ), .ZN(new_n159_));
  NOR2_X1    g138(.A1(new_n136_), .A2(new_n26_), .ZN(new_n160_));
  OR2_X2     g139(.A1(\totalcoeffs[3] ), .A2(\trailingones[0] ), .Z(new_n161_));
  INV_X1     g140(.I(new_n161_), .ZN(new_n162_));
  NOR3_X1    g141(.A1(new_n162_), .A2(new_n67_), .A3(new_n128_), .ZN(new_n163_));
  OAI21_X1   g142(.A1(new_n163_), .A2(new_n160_), .B(new_n51_), .ZN(new_n164_));
  NAND2_X1   g143(.A1(new_n118_), .A2(\totalcoeffs[0] ), .ZN(new_n165_));
  NOR2_X1    g144(.A1(new_n67_), .A2(\ctable[0] ), .ZN(new_n166_));
  INV_X1     g145(.I(new_n166_), .ZN(new_n167_));
  NAND3_X1   g146(.A1(new_n165_), .A2(new_n167_), .A3(new_n148_), .ZN(new_n168_));
  AOI21_X1   g147(.A1(\totalcoeffs[3] ), .A2(\trailingones[0] ), .B(\totalcoeffs[2] ), .ZN(new_n169_));
  NOR2_X1    g148(.A1(new_n169_), .A2(\totalcoeffs[0] ), .ZN(new_n170_));
  AOI21_X1   g149(.A1(new_n168_), .A2(\totalcoeffs[1] ), .B(new_n170_), .ZN(new_n171_));
  AOI21_X1   g150(.A1(new_n171_), .A2(new_n164_), .B(\ctable[1] ), .ZN(new_n172_));
  OAI21_X1   g151(.A1(new_n27_), .A2(\totalcoeffs[1] ), .B(\totalcoeffs[2] ), .ZN(new_n173_));
  NAND2_X1   g152(.A1(new_n51_), .A2(new_n25_), .ZN(new_n174_));
  NAND3_X1   g153(.A1(new_n173_), .A2(new_n174_), .A3(\totalcoeffs[3] ), .ZN(new_n175_));
  NAND2_X1   g154(.A1(new_n51_), .A2(new_n27_), .ZN(new_n176_));
  NOR2_X1    g155(.A1(new_n25_), .A2(\totalcoeffs[0] ), .ZN(new_n177_));
  INV_X1     g156(.I(new_n177_), .ZN(new_n178_));
  NAND4_X1   g157(.A1(new_n178_), .A2(new_n38_), .A3(new_n120_), .A4(new_n176_), .ZN(new_n179_));
  AOI21_X1   g158(.A1(new_n179_), .A2(new_n175_), .B(\ctable[0] ), .ZN(new_n180_));
  OAI21_X1   g159(.A1(new_n172_), .A2(new_n180_), .B(new_n22_), .ZN(new_n181_));
  NOR4_X1    g160(.A1(new_n63_), .A2(new_n61_), .A3(new_n26_), .A4(\trailingones[0] ), .ZN(new_n182_));
  NOR2_X1    g161(.A1(\totalcoeffs[1] ), .A2(\totalcoeffs[2] ), .ZN(new_n183_));
  INV_X1     g162(.I(new_n183_), .ZN(new_n184_));
  NOR3_X1    g163(.A1(new_n184_), .A2(new_n61_), .A3(\trailingones[0] ), .ZN(new_n185_));
  NOR2_X1    g164(.A1(new_n51_), .A2(new_n26_), .ZN(new_n186_));
  OAI21_X1   g165(.A1(new_n185_), .A2(new_n186_), .B(\totalcoeffs[0] ), .ZN(new_n187_));
  NOR2_X1    g166(.A1(new_n63_), .A2(new_n61_), .ZN(new_n188_));
  AOI21_X1   g167(.A1(\ctable[0] ), .A2(new_n105_), .B(new_n188_), .ZN(new_n189_));
  AOI21_X1   g168(.A1(new_n187_), .A2(new_n189_), .B(new_n27_), .ZN(new_n190_));
  OAI21_X1   g169(.A1(new_n190_), .A2(new_n182_), .B(\trailingones[1] ), .ZN(new_n191_));
  AOI21_X1   g170(.A1(new_n181_), .A2(new_n191_), .B(\totalcoeffs[4] ), .ZN(new_n192_));
  OAI21_X1   g171(.A1(new_n159_), .A2(new_n192_), .B(new_n43_), .ZN(new_n193_));
  NAND2_X1   g172(.A1(new_n193_), .A2(new_n125_), .ZN(\coeff_token[1] ));
  NOR2_X1    g173(.A1(new_n119_), .A2(new_n174_), .ZN(new_n195_));
  NAND3_X1   g174(.A1(new_n82_), .A2(\ctable[2] ), .A3(\trailingones[0] ), .ZN(new_n196_));
  NAND2_X1   g175(.A1(new_n196_), .A2(new_n134_), .ZN(new_n197_));
  AOI21_X1   g176(.A1(new_n197_), .A2(\totalcoeffs[1] ), .B(new_n195_), .ZN(new_n198_));
  NOR2_X1    g177(.A1(\ctable[0] ), .A2(\ctable[1] ), .ZN(new_n199_));
  NAND3_X1   g178(.A1(new_n57_), .A2(new_n199_), .A3(new_n34_), .ZN(new_n200_));
  NAND2_X1   g179(.A1(new_n22_), .A2(\trailingones[0] ), .ZN(new_n201_));
  INV_X1     g180(.I(new_n201_), .ZN(new_n202_));
  OAI21_X1   g181(.A1(\ctable[1] ), .A2(\trailingones[0] ), .B(new_n26_), .ZN(new_n203_));
  NOR3_X1    g182(.A1(new_n184_), .A2(\totalcoeffs[3] ), .A3(new_n34_), .ZN(new_n204_));
  OAI21_X1   g183(.A1(new_n202_), .A2(new_n203_), .B(new_n204_), .ZN(new_n205_));
  NOR2_X1    g184(.A1(new_n27_), .A2(\ctable[0] ), .ZN(new_n206_));
  NAND3_X1   g185(.A1(new_n206_), .A2(new_n25_), .A3(new_n39_), .ZN(new_n207_));
  NOR2_X1    g186(.A1(new_n118_), .A2(new_n61_), .ZN(new_n208_));
  NOR2_X1    g187(.A1(new_n208_), .A2(new_n26_), .ZN(new_n209_));
  NAND2_X1   g188(.A1(new_n26_), .A2(\totalcoeffs[2] ), .ZN(new_n210_));
  AOI21_X1   g189(.A1(new_n210_), .A2(\totalcoeffs[3] ), .B(new_n25_), .ZN(new_n211_));
  OAI21_X1   g190(.A1(new_n209_), .A2(new_n211_), .B(\totalcoeffs[1] ), .ZN(new_n212_));
  AOI21_X1   g191(.A1(new_n212_), .A2(new_n207_), .B(\trailingones[1] ), .ZN(new_n213_));
  NAND2_X1   g192(.A1(\totalcoeffs[1] ), .A2(\trailingones[0] ), .ZN(new_n214_));
  AOI21_X1   g193(.A1(new_n214_), .A2(\ctable[1] ), .B(\trailingones[1] ), .ZN(new_n215_));
  OAI22_X1   g194(.A1(new_n215_), .A2(\totalcoeffs[2] ), .B1(\totalcoeffs[1] ), .B2(new_n147_), .ZN(new_n216_));
  NAND2_X1   g195(.A1(new_n216_), .A2(\totalcoeffs[3] ), .ZN(new_n217_));
  NOR2_X1    g196(.A1(new_n25_), .A2(\ctable[1] ), .ZN(new_n218_));
  OAI22_X1   g197(.A1(new_n218_), .A2(new_n38_), .B1(new_n169_), .B2(\totalcoeffs[1] ), .ZN(new_n219_));
  NAND2_X1   g198(.A1(new_n219_), .A2(\ctable[0] ), .ZN(new_n220_));
  OAI21_X1   g199(.A1(new_n51_), .A2(\totalcoeffs[3] ), .B(new_n147_), .ZN(new_n221_));
  NOR2_X1    g200(.A1(new_n22_), .A2(\totalcoeffs[3] ), .ZN(new_n222_));
  NOR2_X1    g201(.A1(new_n222_), .A2(\ctable[1] ), .ZN(new_n223_));
  NOR2_X1    g202(.A1(new_n27_), .A2(\trailingones[0] ), .ZN(new_n224_));
  NOR3_X1    g203(.A1(new_n51_), .A2(new_n22_), .A3(\totalcoeffs[3] ), .ZN(new_n225_));
  AOI22_X1   g204(.A1(new_n221_), .A2(new_n223_), .B1(new_n225_), .B2(new_n224_), .ZN(new_n226_));
  NAND3_X1   g205(.A1(new_n217_), .A2(new_n226_), .A3(new_n220_), .ZN(new_n227_));
  OAI21_X1   g206(.A1(new_n213_), .A2(new_n227_), .B(new_n34_), .ZN(new_n228_));
  AOI21_X1   g207(.A1(new_n228_), .A2(new_n205_), .B(\totalcoeffs[0] ), .ZN(new_n229_));
  NAND2_X1   g208(.A1(new_n147_), .A2(new_n201_), .ZN(new_n230_));
  OAI21_X1   g209(.A1(new_n230_), .A2(new_n106_), .B(\totalcoeffs[2] ), .ZN(new_n231_));
  OR2_X2     g210(.A1(\trailingones[0] ), .A2(\trailingones[1] ), .Z(new_n232_));
  NAND2_X1   g211(.A1(new_n82_), .A2(\trailingones[0] ), .ZN(new_n233_));
  AOI21_X1   g212(.A1(new_n233_), .A2(new_n232_), .B(new_n26_), .ZN(new_n234_));
  NOR2_X1    g213(.A1(new_n95_), .A2(\ctable[0] ), .ZN(new_n235_));
  OAI21_X1   g214(.A1(new_n234_), .A2(new_n235_), .B(\totalcoeffs[1] ), .ZN(new_n236_));
  AOI21_X1   g215(.A1(new_n236_), .A2(new_n231_), .B(\totalcoeffs[3] ), .ZN(new_n237_));
  NOR2_X1    g216(.A1(new_n25_), .A2(\totalcoeffs[1] ), .ZN(new_n238_));
  NAND3_X1   g217(.A1(new_n105_), .A2(new_n238_), .A3(\trailingones[1] ), .ZN(new_n239_));
  OAI21_X1   g218(.A1(new_n61_), .A2(\totalcoeffs[1] ), .B(\ctable[0] ), .ZN(new_n240_));
  NAND3_X1   g219(.A1(new_n240_), .A2(new_n38_), .A3(new_n32_), .ZN(new_n241_));
  AOI21_X1   g220(.A1(new_n241_), .A2(new_n239_), .B(new_n67_), .ZN(new_n242_));
  OAI21_X1   g221(.A1(new_n237_), .A2(new_n242_), .B(new_n27_), .ZN(new_n243_));
  NOR2_X1    g222(.A1(new_n51_), .A2(new_n22_), .ZN(new_n244_));
  INV_X1     g223(.I(new_n244_), .ZN(new_n245_));
  NOR2_X1    g224(.A1(new_n245_), .A2(new_n38_), .ZN(new_n246_));
  OAI21_X1   g225(.A1(new_n246_), .A2(new_n238_), .B(\ctable[1] ), .ZN(new_n247_));
  AOI22_X1   g226(.A1(new_n47_), .A2(\trailingones[0] ), .B1(\totalcoeffs[2] ), .B2(new_n32_), .ZN(new_n248_));
  AOI21_X1   g227(.A1(new_n247_), .A2(new_n248_), .B(new_n61_), .ZN(new_n249_));
  OR2_X2     g228(.A1(new_n244_), .A2(new_n106_), .Z(new_n250_));
  NAND2_X1   g229(.A1(new_n250_), .A2(new_n162_), .ZN(new_n251_));
  NOR2_X1    g230(.A1(new_n72_), .A2(new_n27_), .ZN(new_n252_));
  OAI21_X1   g231(.A1(new_n252_), .A2(new_n76_), .B(\trailingones[0] ), .ZN(new_n253_));
  AOI21_X1   g232(.A1(new_n251_), .A2(new_n253_), .B(\totalcoeffs[2] ), .ZN(new_n254_));
  OAI21_X1   g233(.A1(new_n249_), .A2(new_n254_), .B(new_n166_), .ZN(new_n255_));
  AOI21_X1   g234(.A1(new_n243_), .A2(new_n255_), .B(\totalcoeffs[4] ), .ZN(new_n256_));
  NOR2_X1    g235(.A1(new_n256_), .A2(new_n229_), .ZN(new_n257_));
  OAI22_X1   g236(.A1(new_n257_), .A2(\ctable[2] ), .B1(new_n198_), .B2(new_n200_), .ZN(\coeff_token[2] ));
  INV_X1     g237(.I(new_n142_), .ZN(new_n259_));
  NOR2_X1    g238(.A1(new_n26_), .A2(new_n25_), .ZN(new_n260_));
  NAND2_X1   g239(.A1(new_n259_), .A2(new_n260_), .ZN(new_n261_));
  AOI21_X1   g240(.A1(new_n261_), .A2(new_n131_), .B(new_n38_), .ZN(new_n262_));
  INV_X1     g241(.I(new_n206_), .ZN(new_n263_));
  NOR2_X1    g242(.A1(new_n218_), .A2(new_n26_), .ZN(new_n264_));
  OAI22_X1   g243(.A1(new_n264_), .A2(new_n61_), .B1(new_n263_), .B2(\trailingones[0] ), .ZN(new_n265_));
  OAI21_X1   g244(.A1(new_n262_), .A2(new_n265_), .B(\totalcoeffs[1] ), .ZN(new_n266_));
  NAND2_X1   g245(.A1(new_n206_), .A2(\totalcoeffs[2] ), .ZN(new_n267_));
  AOI21_X1   g246(.A1(new_n266_), .A2(new_n267_), .B(\totalcoeffs[4] ), .ZN(new_n268_));
  NOR2_X1    g247(.A1(new_n34_), .A2(\totalcoeffs[3] ), .ZN(new_n269_));
  INV_X1     g248(.I(new_n199_), .ZN(new_n270_));
  NAND2_X1   g249(.A1(\trailingones[0] ), .A2(\trailingones[1] ), .ZN(new_n271_));
  OAI21_X1   g250(.A1(new_n270_), .A2(new_n271_), .B(new_n29_), .ZN(new_n272_));
  NAND3_X1   g251(.A1(new_n272_), .A2(new_n38_), .A3(new_n269_), .ZN(new_n273_));
  OAI22_X1   g252(.A1(new_n259_), .A2(new_n61_), .B1(new_n38_), .B2(new_n27_), .ZN(new_n274_));
  NAND2_X1   g253(.A1(new_n274_), .A2(new_n34_), .ZN(new_n275_));
  AOI21_X1   g254(.A1(new_n273_), .A2(new_n275_), .B(\totalcoeffs[1] ), .ZN(new_n276_));
  OAI21_X1   g255(.A1(new_n268_), .A2(new_n276_), .B(new_n67_), .ZN(new_n277_));
  NOR3_X1    g256(.A1(new_n136_), .A2(new_n176_), .A3(new_n26_), .ZN(new_n278_));
  NOR2_X1    g257(.A1(new_n263_), .A2(\totalcoeffs[3] ), .ZN(new_n279_));
  OAI21_X1   g258(.A1(new_n279_), .A2(new_n278_), .B(new_n22_), .ZN(new_n280_));
  OAI21_X1   g259(.A1(new_n162_), .A2(new_n128_), .B(\totalcoeffs[2] ), .ZN(new_n281_));
  NAND2_X1   g260(.A1(new_n260_), .A2(new_n38_), .ZN(new_n282_));
  AOI21_X1   g261(.A1(new_n281_), .A2(new_n282_), .B(\trailingones[1] ), .ZN(new_n283_));
  NAND2_X1   g262(.A1(\ctable[0] ), .A2(\trailingones[1] ), .ZN(new_n284_));
  OAI21_X1   g263(.A1(new_n284_), .A2(\trailingones[0] ), .B(new_n61_), .ZN(new_n285_));
  NAND2_X1   g264(.A1(new_n285_), .A2(new_n38_), .ZN(new_n286_));
  NAND2_X1   g265(.A1(new_n26_), .A2(\totalcoeffs[3] ), .ZN(new_n287_));
  OAI21_X1   g266(.A1(new_n61_), .A2(\trailingones[0] ), .B(new_n27_), .ZN(new_n288_));
  NAND2_X1   g267(.A1(new_n288_), .A2(new_n287_), .ZN(new_n289_));
  NAND2_X1   g268(.A1(new_n286_), .A2(new_n289_), .ZN(new_n290_));
  OAI21_X1   g269(.A1(new_n283_), .A2(new_n290_), .B(\totalcoeffs[1] ), .ZN(new_n291_));
  AOI21_X1   g270(.A1(new_n291_), .A2(new_n280_), .B(new_n67_), .ZN(new_n292_));
  AOI22_X1   g271(.A1(new_n206_), .A2(new_n22_), .B1(\totalcoeffs[3] ), .B2(new_n27_), .ZN(new_n293_));
  NOR2_X1    g272(.A1(new_n293_), .A2(\trailingones[0] ), .ZN(new_n294_));
  NAND3_X1   g273(.A1(new_n27_), .A2(\totalcoeffs[2] ), .A3(\totalcoeffs[3] ), .ZN(new_n295_));
  NAND2_X1   g274(.A1(new_n105_), .A2(new_n206_), .ZN(new_n296_));
  AOI21_X1   g275(.A1(new_n296_), .A2(new_n295_), .B(new_n22_), .ZN(new_n297_));
  OAI21_X1   g276(.A1(new_n294_), .A2(new_n297_), .B(new_n51_), .ZN(new_n298_));
  NOR2_X1    g277(.A1(new_n201_), .A2(new_n51_), .ZN(new_n299_));
  NOR2_X1    g278(.A1(new_n244_), .A2(new_n260_), .ZN(new_n300_));
  NAND2_X1   g279(.A1(new_n284_), .A2(new_n27_), .ZN(new_n301_));
  NOR2_X1    g280(.A1(new_n52_), .A2(new_n153_), .ZN(new_n302_));
  OAI22_X1   g281(.A1(new_n300_), .A2(new_n301_), .B1(\totalcoeffs[2] ), .B2(new_n302_), .ZN(new_n303_));
  AOI22_X1   g282(.A1(new_n303_), .A2(\totalcoeffs[3] ), .B1(new_n206_), .B2(new_n299_), .ZN(new_n304_));
  NAND2_X1   g283(.A1(new_n304_), .A2(new_n298_), .ZN(new_n305_));
  OAI21_X1   g284(.A1(new_n292_), .A2(new_n305_), .B(new_n34_), .ZN(new_n306_));
  AOI21_X1   g285(.A1(new_n306_), .A2(new_n277_), .B(\ctable[2] ), .ZN(\coeff_token[3] ));
  NAND3_X1   g286(.A1(new_n46_), .A2(\totalcoeffs[2] ), .A3(new_n34_), .ZN(new_n308_));
  NOR2_X1    g287(.A1(new_n184_), .A2(\totalcoeffs[0] ), .ZN(new_n309_));
  NOR2_X1    g288(.A1(new_n61_), .A2(\totalcoeffs[4] ), .ZN(new_n310_));
  OAI21_X1   g289(.A1(new_n269_), .A2(new_n310_), .B(new_n309_), .ZN(new_n311_));
  NAND2_X1   g290(.A1(new_n28_), .A2(new_n43_), .ZN(new_n312_));
  AOI21_X1   g291(.A1(new_n311_), .A2(new_n308_), .B(new_n312_), .ZN(\coeff_token[4] ));
  NAND3_X1   g292(.A1(new_n269_), .A2(new_n38_), .A3(new_n45_), .ZN(new_n314_));
  INV_X1     g293(.I(new_n309_), .ZN(new_n315_));
  NAND2_X1   g294(.A1(new_n315_), .A2(new_n310_), .ZN(new_n316_));
  AOI21_X1   g295(.A1(new_n316_), .A2(new_n314_), .B(new_n312_), .ZN(\coeff_token[5] ));
  NAND4_X1   g296(.A1(new_n57_), .A2(new_n67_), .A3(new_n51_), .A4(\totalcoeffs[4] ), .ZN(new_n318_));
  NAND2_X1   g297(.A1(new_n29_), .A2(new_n318_), .ZN(new_n319_));
  OAI21_X1   g298(.A1(new_n245_), .A2(new_n135_), .B(new_n232_), .ZN(new_n320_));
  NAND3_X1   g299(.A1(new_n320_), .A2(new_n38_), .A3(\ctable[2] ), .ZN(new_n321_));
  AOI21_X1   g300(.A1(\ctable[2] ), .A2(new_n22_), .B(new_n25_), .ZN(new_n322_));
  NOR3_X1    g301(.A1(new_n322_), .A2(\totalcoeffs[1] ), .A3(new_n38_), .ZN(new_n323_));
  OAI21_X1   g302(.A1(new_n98_), .A2(new_n323_), .B(new_n67_), .ZN(new_n324_));
  NAND2_X1   g303(.A1(new_n321_), .A2(new_n324_), .ZN(new_n325_));
  NOR2_X1    g304(.A1(\totalcoeffs[1] ), .A2(\ctable[0] ), .ZN(new_n326_));
  NOR2_X1    g305(.A1(\ctable[1] ), .A2(\trailingones[1] ), .ZN(new_n327_));
  OAI21_X1   g306(.A1(new_n38_), .A2(new_n326_), .B(new_n327_), .ZN(new_n328_));
  NAND2_X1   g307(.A1(new_n244_), .A2(\ctable[0] ), .ZN(new_n329_));
  AOI21_X1   g308(.A1(new_n329_), .A2(new_n328_), .B(new_n67_), .ZN(new_n330_));
  NAND2_X1   g309(.A1(new_n67_), .A2(\totalcoeffs[2] ), .ZN(new_n331_));
  NOR2_X1    g310(.A1(new_n331_), .A2(new_n52_), .ZN(new_n332_));
  OAI21_X1   g311(.A1(new_n330_), .A2(new_n332_), .B(\trailingones[0] ), .ZN(new_n333_));
  AOI21_X1   g312(.A1(new_n232_), .A2(new_n271_), .B(new_n27_), .ZN(new_n334_));
  NAND2_X1   g313(.A1(new_n38_), .A2(\trailingones[1] ), .ZN(new_n335_));
  AND2_X2    g314(.A1(new_n47_), .A2(new_n335_), .Z(new_n336_));
  OAI21_X1   g315(.A1(new_n38_), .A2(new_n68_), .B(new_n107_), .ZN(new_n337_));
  AOI22_X1   g316(.A1(\ctable[0] ), .A2(new_n337_), .B1(new_n336_), .B2(new_n334_), .ZN(new_n338_));
  NAND2_X1   g317(.A1(new_n333_), .A2(new_n338_), .ZN(new_n339_));
  AOI22_X1   g318(.A1(new_n339_), .A2(new_n43_), .B1(new_n199_), .B2(new_n325_), .ZN(new_n340_));
  AOI21_X1   g319(.A1(new_n245_), .A2(new_n107_), .B(new_n67_), .ZN(new_n341_));
  NAND3_X1   g320(.A1(new_n174_), .A2(new_n67_), .A3(new_n27_), .ZN(new_n342_));
  OAI22_X1   g321(.A1(new_n250_), .A2(new_n342_), .B1(new_n38_), .B2(new_n97_), .ZN(new_n343_));
  OAI21_X1   g322(.A1(new_n343_), .A2(new_n341_), .B(new_n26_), .ZN(new_n344_));
  AOI22_X1   g323(.A1(new_n150_), .A2(\totalcoeffs[0] ), .B1(\totalcoeffs[1] ), .B2(new_n25_), .ZN(new_n345_));
  OAI22_X1   g324(.A1(new_n345_), .A2(\totalcoeffs[2] ), .B1(\trailingones[0] ), .B2(new_n120_), .ZN(new_n346_));
  NAND2_X1   g325(.A1(new_n67_), .A2(new_n25_), .ZN(new_n347_));
  NOR2_X1    g326(.A1(new_n97_), .A2(new_n166_), .ZN(new_n348_));
  AOI22_X1   g327(.A1(new_n346_), .A2(\trailingones[1] ), .B1(new_n347_), .B2(new_n348_), .ZN(new_n349_));
  NAND2_X1   g328(.A1(new_n344_), .A2(new_n349_), .ZN(new_n350_));
  NAND2_X1   g329(.A1(\totalcoeffs[2] ), .A2(\trailingones[0] ), .ZN(new_n351_));
  NOR2_X1    g330(.A1(new_n68_), .A2(new_n351_), .ZN(new_n352_));
  OAI21_X1   g331(.A1(\totalcoeffs[0] ), .A2(\ctable[1] ), .B(new_n25_), .ZN(new_n353_));
  NAND2_X1   g332(.A1(new_n38_), .A2(new_n22_), .ZN(new_n354_));
  AOI21_X1   g333(.A1(new_n167_), .A2(new_n353_), .B(new_n354_), .ZN(new_n355_));
  OAI21_X1   g334(.A1(new_n355_), .A2(new_n352_), .B(new_n51_), .ZN(new_n356_));
  NAND2_X1   g335(.A1(new_n38_), .A2(\ctable[0] ), .ZN(new_n357_));
  AOI21_X1   g336(.A1(new_n26_), .A2(\totalcoeffs[2] ), .B(\ctable[1] ), .ZN(new_n358_));
  OAI22_X1   g337(.A1(new_n84_), .A2(new_n357_), .B1(new_n358_), .B2(new_n68_), .ZN(new_n359_));
  OAI21_X1   g338(.A1(\trailingones[0] ), .A2(\trailingones[1] ), .B(\totalcoeffs[2] ), .ZN(new_n360_));
  NAND2_X1   g339(.A1(new_n233_), .A2(new_n360_), .ZN(new_n361_));
  AOI22_X1   g340(.A1(new_n359_), .A2(new_n25_), .B1(\ctable[1] ), .B2(new_n361_), .ZN(new_n362_));
  OAI21_X1   g341(.A1(new_n362_), .A2(new_n51_), .B(new_n356_), .ZN(new_n363_));
  AOI21_X1   g342(.A1(new_n350_), .A2(\totalcoeffs[3] ), .B(new_n363_), .ZN(new_n364_));
  OAI22_X1   g343(.A1(new_n364_), .A2(\ctable[2] ), .B1(\totalcoeffs[3] ), .B2(new_n340_), .ZN(new_n365_));
  AOI22_X1   g344(.A1(new_n365_), .A2(new_n34_), .B1(new_n43_), .B2(new_n319_), .ZN(\ctoken_len[0] ));
  NOR2_X1    g345(.A1(\totalcoeffs[0] ), .A2(\totalcoeffs[3] ), .ZN(new_n367_));
  NAND2_X1   g346(.A1(new_n62_), .A2(new_n367_), .ZN(new_n368_));
  NOR4_X1    g347(.A1(new_n368_), .A2(new_n34_), .A3(\ctable[2] ), .A4(new_n176_), .ZN(new_n369_));
  NAND2_X1   g348(.A1(new_n96_), .A2(new_n140_), .ZN(new_n370_));
  NAND2_X1   g349(.A1(new_n22_), .A2(\ctable[0] ), .ZN(new_n371_));
  NOR2_X1    g350(.A1(new_n371_), .A2(\totalcoeffs[0] ), .ZN(new_n372_));
  AOI21_X1   g351(.A1(new_n47_), .A2(new_n335_), .B(new_n67_), .ZN(new_n373_));
  OAI21_X1   g352(.A1(new_n373_), .A2(new_n372_), .B(\trailingones[0] ), .ZN(new_n374_));
  AOI21_X1   g353(.A1(new_n374_), .A2(new_n370_), .B(\totalcoeffs[3] ), .ZN(new_n375_));
  NOR3_X1    g354(.A1(new_n61_), .A2(new_n26_), .A3(\totalcoeffs[2] ), .ZN(new_n376_));
  NAND2_X1   g355(.A1(\totalcoeffs[3] ), .A2(\ctable[0] ), .ZN(new_n377_));
  NAND2_X1   g356(.A1(new_n47_), .A2(new_n377_), .ZN(new_n378_));
  AOI21_X1   g357(.A1(new_n378_), .A2(new_n67_), .B(new_n376_), .ZN(new_n379_));
  NAND2_X1   g358(.A1(new_n38_), .A2(\totalcoeffs[3] ), .ZN(new_n380_));
  OAI22_X1   g359(.A1(new_n379_), .A2(\trailingones[0] ), .B1(new_n371_), .B2(new_n380_), .ZN(new_n381_));
  OAI21_X1   g360(.A1(new_n375_), .A2(new_n381_), .B(\totalcoeffs[1] ), .ZN(new_n382_));
  NAND4_X1   g361(.A1(new_n32_), .A2(\totalcoeffs[0] ), .A3(\totalcoeffs[2] ), .A4(\totalcoeffs[3] ), .ZN(new_n383_));
  NAND2_X1   g362(.A1(new_n232_), .A2(new_n271_), .ZN(new_n384_));
  NOR2_X1    g363(.A1(new_n38_), .A2(new_n61_), .ZN(new_n385_));
  NAND2_X1   g364(.A1(new_n58_), .A2(new_n38_), .ZN(new_n386_));
  AOI21_X1   g365(.A1(new_n384_), .A2(new_n386_), .B(new_n385_), .ZN(new_n387_));
  OAI21_X1   g366(.A1(new_n387_), .A2(new_n26_), .B(new_n383_), .ZN(new_n388_));
  NOR4_X1    g367(.A1(new_n284_), .A2(new_n38_), .A3(new_n61_), .A4(new_n25_), .ZN(new_n389_));
  AOI21_X1   g368(.A1(new_n388_), .A2(new_n51_), .B(new_n389_), .ZN(new_n390_));
  AOI21_X1   g369(.A1(new_n382_), .A2(new_n390_), .B(\ctable[1] ), .ZN(new_n391_));
  NOR4_X1    g370(.A1(new_n61_), .A2(new_n25_), .A3(\totalcoeffs[0] ), .A4(\ctable[1] ), .ZN(new_n392_));
  OAI21_X1   g371(.A1(new_n392_), .A2(new_n224_), .B(\trailingones[1] ), .ZN(new_n393_));
  OAI21_X1   g372(.A1(\totalcoeffs[3] ), .A2(new_n25_), .B(new_n126_), .ZN(new_n394_));
  AOI22_X1   g373(.A1(new_n394_), .A2(\totalcoeffs[0] ), .B1(new_n22_), .B2(new_n150_), .ZN(new_n395_));
  AOI21_X1   g374(.A1(new_n395_), .A2(new_n393_), .B(\totalcoeffs[2] ), .ZN(new_n396_));
  NOR2_X1    g375(.A1(new_n271_), .A2(\totalcoeffs[3] ), .ZN(new_n397_));
  NAND2_X1   g376(.A1(new_n271_), .A2(\totalcoeffs[3] ), .ZN(new_n398_));
  NAND2_X1   g377(.A1(new_n398_), .A2(new_n135_), .ZN(new_n399_));
  AOI21_X1   g378(.A1(new_n399_), .A2(new_n27_), .B(new_n397_), .ZN(new_n400_));
  NAND3_X1   g379(.A1(new_n32_), .A2(new_n61_), .A3(new_n27_), .ZN(new_n401_));
  OAI21_X1   g380(.A1(new_n400_), .A2(new_n38_), .B(new_n401_), .ZN(new_n402_));
  OAI21_X1   g381(.A1(new_n402_), .A2(new_n396_), .B(\totalcoeffs[1] ), .ZN(new_n403_));
  NOR4_X1    g382(.A1(new_n380_), .A2(new_n27_), .A3(\trailingones[0] ), .A4(\trailingones[1] ), .ZN(new_n404_));
  MUX2_X1    g383(.I0(new_n67_), .I1(new_n25_), .S(\trailingones[1] ), .Z(new_n405_));
  NOR2_X1    g384(.A1(\totalcoeffs[2] ), .A2(\ctable[1] ), .ZN(new_n406_));
  AOI22_X1   g385(.A1(new_n334_), .A2(new_n67_), .B1(new_n405_), .B2(new_n406_), .ZN(new_n407_));
  NAND3_X1   g386(.A1(\totalcoeffs[0] ), .A2(\ctable[1] ), .A3(\trailingones[0] ), .ZN(new_n408_));
  OR3_X2     g387(.A1(\totalcoeffs[0] ), .A2(\totalcoeffs[2] ), .A3(\trailingones[0] ), .Z(new_n409_));
  AOI21_X1   g388(.A1(new_n409_), .A2(new_n408_), .B(\trailingones[1] ), .ZN(new_n410_));
  AOI21_X1   g389(.A1(new_n161_), .A2(new_n27_), .B(new_n360_), .ZN(new_n411_));
  NOR2_X1    g390(.A1(new_n410_), .A2(new_n411_), .ZN(new_n412_));
  OAI21_X1   g391(.A1(new_n407_), .A2(new_n61_), .B(new_n412_), .ZN(new_n413_));
  AOI21_X1   g392(.A1(new_n413_), .A2(new_n51_), .B(new_n404_), .ZN(new_n414_));
  AOI21_X1   g393(.A1(new_n414_), .A2(new_n403_), .B(\ctable[0] ), .ZN(new_n415_));
  OAI21_X1   g394(.A1(new_n415_), .A2(new_n391_), .B(new_n43_), .ZN(new_n416_));
  AOI21_X1   g395(.A1(new_n147_), .A2(new_n201_), .B(new_n331_), .ZN(new_n417_));
  NOR3_X1    g396(.A1(new_n54_), .A2(\trailingones[1] ), .A3(new_n44_), .ZN(new_n418_));
  NOR2_X1    g397(.A1(new_n71_), .A2(new_n176_), .ZN(new_n419_));
  OAI21_X1   g398(.A1(new_n417_), .A2(new_n418_), .B(new_n419_), .ZN(new_n420_));
  NAND2_X1   g399(.A1(new_n416_), .A2(new_n420_), .ZN(new_n421_));
  AOI21_X1   g400(.A1(new_n421_), .A2(new_n34_), .B(new_n369_), .ZN(\ctoken_len[1] ));
  NOR4_X1    g401(.A1(new_n315_), .A2(new_n71_), .A3(new_n34_), .A4(\ctable[2] ), .ZN(new_n423_));
  AOI21_X1   g402(.A1(new_n232_), .A2(new_n51_), .B(new_n38_), .ZN(new_n424_));
  OAI21_X1   g403(.A1(new_n424_), .A2(new_n252_), .B(\totalcoeffs[0] ), .ZN(new_n425_));
  OAI21_X1   g404(.A1(new_n51_), .A2(\trailingones[0] ), .B(new_n27_), .ZN(new_n426_));
  NAND2_X1   g405(.A1(new_n97_), .A2(\trailingones[0] ), .ZN(new_n427_));
  AOI22_X1   g406(.A1(new_n427_), .A2(new_n252_), .B1(\totalcoeffs[2] ), .B2(new_n426_), .ZN(new_n428_));
  AOI21_X1   g407(.A1(new_n428_), .A2(new_n425_), .B(new_n287_), .ZN(new_n429_));
  NOR2_X1    g408(.A1(new_n26_), .A2(\totalcoeffs[1] ), .ZN(new_n430_));
  NOR2_X1    g409(.A1(new_n430_), .A2(new_n70_), .ZN(new_n431_));
  NOR4_X1    g410(.A1(new_n431_), .A2(\totalcoeffs[2] ), .A3(new_n106_), .A4(new_n222_), .ZN(new_n432_));
  INV_X1     g411(.I(new_n109_), .ZN(new_n433_));
  NOR3_X1    g412(.A1(new_n244_), .A2(new_n106_), .A3(new_n326_), .ZN(new_n434_));
  NOR2_X1    g413(.A1(new_n26_), .A2(\trailingones[1] ), .ZN(new_n435_));
  AOI21_X1   g414(.A1(new_n183_), .A2(new_n435_), .B(new_n225_), .ZN(new_n436_));
  OAI22_X1   g415(.A1(new_n436_), .A2(\totalcoeffs[0] ), .B1(new_n434_), .B2(new_n433_), .ZN(new_n437_));
  OAI21_X1   g416(.A1(new_n437_), .A2(new_n432_), .B(new_n25_), .ZN(new_n438_));
  NAND3_X1   g417(.A1(new_n377_), .A2(\totalcoeffs[1] ), .A3(\totalcoeffs[2] ), .ZN(new_n439_));
  AOI21_X1   g418(.A1(new_n178_), .A2(new_n26_), .B(new_n439_), .ZN(new_n440_));
  NAND2_X1   g419(.A1(new_n166_), .A2(new_n39_), .ZN(new_n441_));
  NOR2_X1    g420(.A1(new_n367_), .A2(\totalcoeffs[2] ), .ZN(new_n442_));
  OAI21_X1   g421(.A1(new_n70_), .A2(new_n430_), .B(new_n442_), .ZN(new_n443_));
  AOI21_X1   g422(.A1(new_n443_), .A2(new_n441_), .B(new_n25_), .ZN(new_n444_));
  OAI21_X1   g423(.A1(new_n444_), .A2(new_n440_), .B(new_n22_), .ZN(new_n445_));
  OAI21_X1   g424(.A1(new_n118_), .A2(new_n61_), .B(\totalcoeffs[1] ), .ZN(new_n446_));
  AOI21_X1   g425(.A1(new_n210_), .A2(new_n377_), .B(new_n446_), .ZN(new_n447_));
  AND4_X2    g426(.A1(new_n51_), .A2(new_n118_), .A3(new_n148_), .A4(\totalcoeffs[3] ), .Z(new_n448_));
  OAI21_X1   g427(.A1(new_n447_), .A2(new_n448_), .B(\trailingones[1] ), .ZN(new_n449_));
  NAND3_X1   g428(.A1(new_n438_), .A2(new_n445_), .A3(new_n449_), .ZN(new_n450_));
  AOI21_X1   g429(.A1(new_n450_), .A2(new_n27_), .B(new_n429_), .ZN(new_n451_));
  INV_X1     g430(.I(new_n165_), .ZN(new_n452_));
  AOI21_X1   g431(.A1(new_n136_), .A2(new_n351_), .B(\totalcoeffs[0] ), .ZN(new_n453_));
  OAI21_X1   g432(.A1(new_n452_), .A2(new_n453_), .B(new_n22_), .ZN(new_n454_));
  NAND3_X1   g433(.A1(new_n96_), .A2(new_n67_), .A3(new_n25_), .ZN(new_n455_));
  NAND2_X1   g434(.A1(new_n454_), .A2(new_n455_), .ZN(new_n456_));
  NOR2_X1    g435(.A1(new_n245_), .A2(new_n409_), .ZN(new_n457_));
  AOI21_X1   g436(.A1(new_n456_), .A2(new_n51_), .B(new_n457_), .ZN(new_n458_));
  NAND2_X1   g437(.A1(new_n70_), .A2(new_n27_), .ZN(new_n459_));
  OAI22_X1   g438(.A1(new_n451_), .A2(\ctable[2] ), .B1(new_n458_), .B2(new_n459_), .ZN(new_n460_));
  AOI21_X1   g439(.A1(new_n460_), .A2(new_n34_), .B(new_n423_), .ZN(\ctoken_len[2] ));
  INV_X1     g440(.I(new_n52_), .ZN(new_n462_));
  NAND2_X1   g441(.A1(new_n284_), .A2(new_n25_), .ZN(new_n463_));
  NAND4_X1   g442(.A1(new_n463_), .A2(new_n462_), .A3(\totalcoeffs[2] ), .A4(new_n61_), .ZN(new_n464_));
  AOI21_X1   g443(.A1(new_n301_), .A2(new_n177_), .B(new_n127_), .ZN(new_n465_));
  OAI21_X1   g444(.A1(new_n199_), .A2(new_n34_), .B(new_n61_), .ZN(new_n466_));
  OAI21_X1   g445(.A1(new_n465_), .A2(new_n61_), .B(new_n466_), .ZN(new_n467_));
  NAND2_X1   g446(.A1(new_n467_), .A2(new_n38_), .ZN(new_n468_));
  AOI21_X1   g447(.A1(new_n468_), .A2(new_n464_), .B(\totalcoeffs[1] ), .ZN(new_n469_));
  NAND2_X1   g448(.A1(new_n462_), .A2(new_n61_), .ZN(new_n470_));
  OAI21_X1   g449(.A1(new_n127_), .A2(new_n61_), .B(new_n177_), .ZN(new_n471_));
  AOI21_X1   g450(.A1(new_n471_), .A2(new_n470_), .B(\totalcoeffs[2] ), .ZN(new_n472_));
  NOR2_X1    g451(.A1(new_n284_), .A2(new_n25_), .ZN(new_n473_));
  NOR2_X1    g452(.A1(new_n473_), .A2(\ctable[1] ), .ZN(new_n474_));
  NAND2_X1   g453(.A1(new_n271_), .A2(new_n26_), .ZN(new_n475_));
  OAI22_X1   g454(.A1(new_n474_), .A2(\totalcoeffs[3] ), .B1(new_n295_), .B2(new_n475_), .ZN(new_n476_));
  NOR2_X1    g455(.A1(new_n476_), .A2(new_n472_), .ZN(new_n477_));
  NOR2_X1    g456(.A1(new_n477_), .A2(new_n51_), .ZN(new_n478_));
  NAND4_X1   g457(.A1(new_n166_), .A2(\totalcoeffs[2] ), .A3(\totalcoeffs[3] ), .A4(new_n27_), .ZN(new_n479_));
  AOI22_X1   g458(.A1(new_n479_), .A2(new_n43_), .B1(new_n51_), .B2(new_n232_), .ZN(new_n480_));
  NAND2_X1   g459(.A1(new_n40_), .A2(new_n43_), .ZN(new_n481_));
  NAND2_X1   g460(.A1(new_n481_), .A2(\totalcoeffs[0] ), .ZN(new_n482_));
  OAI21_X1   g461(.A1(new_n109_), .A2(\ctable[0] ), .B(\ctable[1] ), .ZN(new_n483_));
  AOI22_X1   g462(.A1(new_n433_), .A2(\ctable[2] ), .B1(\totalcoeffs[4] ), .B2(new_n40_), .ZN(new_n484_));
  NAND3_X1   g463(.A1(new_n482_), .A2(new_n484_), .A3(new_n483_), .ZN(new_n485_));
  NOR4_X1    g464(.A1(new_n469_), .A2(new_n478_), .A3(new_n480_), .A4(new_n485_), .ZN(\ctoken_len[3] ));
  INV_X1     g465(.I(new_n69_), .ZN(new_n487_));
  AOI21_X1   g466(.A1(new_n119_), .A2(new_n51_), .B(\trailingones[0] ), .ZN(new_n488_));
  NOR3_X1    g467(.A1(new_n38_), .A2(new_n61_), .A3(\totalcoeffs[4] ), .ZN(new_n489_));
  OAI21_X1   g468(.A1(new_n488_), .A2(new_n487_), .B(new_n489_), .ZN(new_n490_));
  NAND2_X1   g469(.A1(new_n199_), .A2(new_n43_), .ZN(new_n491_));
  AOI21_X1   g470(.A1(new_n490_), .A2(new_n314_), .B(new_n491_), .ZN(\ctoken_len[4] ));
endmodule


