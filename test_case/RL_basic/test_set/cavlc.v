// Benchmark "top" written by ABC on Fri Feb 25 15:09:03 2022

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
    new_n117_, new_n118_, new_n119_, new_n120_, new_n121_, new_n122_,
    new_n123_, new_n124_, new_n125_, new_n126_, new_n127_, new_n128_,
    new_n129_, new_n130_, new_n131_, new_n132_, new_n133_, new_n134_,
    new_n135_, new_n136_, new_n137_, new_n138_, new_n139_, new_n140_,
    new_n141_, new_n142_, new_n144_, new_n145_, new_n146_, new_n147_,
    new_n148_, new_n149_, new_n150_, new_n151_, new_n152_, new_n153_,
    new_n154_, new_n155_, new_n156_, new_n157_, new_n158_, new_n159_,
    new_n160_, new_n161_, new_n162_, new_n163_, new_n164_, new_n165_,
    new_n166_, new_n167_, new_n168_, new_n169_, new_n170_, new_n171_,
    new_n172_, new_n173_, new_n174_, new_n175_, new_n176_, new_n177_,
    new_n178_, new_n179_, new_n180_, new_n181_, new_n182_, new_n183_,
    new_n184_, new_n185_, new_n186_, new_n187_, new_n188_, new_n189_,
    new_n190_, new_n191_, new_n192_, new_n193_, new_n194_, new_n195_,
    new_n196_, new_n197_, new_n198_, new_n199_, new_n200_, new_n201_,
    new_n202_, new_n203_, new_n204_, new_n205_, new_n206_, new_n207_,
    new_n208_, new_n209_, new_n210_, new_n211_, new_n212_, new_n213_,
    new_n214_, new_n215_, new_n216_, new_n217_, new_n218_, new_n219_,
    new_n220_, new_n221_, new_n222_, new_n223_, new_n224_, new_n225_,
    new_n226_, new_n227_, new_n228_, new_n229_, new_n230_, new_n231_,
    new_n232_, new_n233_, new_n234_, new_n235_, new_n236_, new_n237_,
    new_n238_, new_n239_, new_n240_, new_n241_, new_n242_, new_n243_,
    new_n244_, new_n245_, new_n246_, new_n247_, new_n248_, new_n249_,
    new_n250_, new_n251_, new_n252_, new_n253_, new_n255_, new_n256_,
    new_n257_, new_n258_, new_n259_, new_n260_, new_n261_, new_n262_,
    new_n263_, new_n264_, new_n265_, new_n266_, new_n267_, new_n268_,
    new_n269_, new_n270_, new_n271_, new_n272_, new_n273_, new_n274_,
    new_n275_, new_n276_, new_n277_, new_n278_, new_n279_, new_n280_,
    new_n281_, new_n282_, new_n283_, new_n284_, new_n285_, new_n286_,
    new_n287_, new_n288_, new_n289_, new_n290_, new_n291_, new_n292_,
    new_n293_, new_n294_, new_n295_, new_n296_, new_n297_, new_n298_,
    new_n299_, new_n300_, new_n301_, new_n302_, new_n303_, new_n304_,
    new_n305_, new_n306_, new_n307_, new_n308_, new_n309_, new_n310_,
    new_n311_, new_n312_, new_n313_, new_n314_, new_n315_, new_n316_,
    new_n317_, new_n318_, new_n319_, new_n320_, new_n321_, new_n322_,
    new_n323_, new_n324_, new_n325_, new_n326_, new_n327_, new_n328_,
    new_n329_, new_n330_, new_n331_, new_n332_, new_n333_, new_n334_,
    new_n335_, new_n336_, new_n337_, new_n338_, new_n339_, new_n340_,
    new_n341_, new_n342_, new_n343_, new_n344_, new_n345_, new_n346_,
    new_n347_, new_n348_, new_n349_, new_n350_, new_n352_, new_n353_,
    new_n354_, new_n355_, new_n356_, new_n357_, new_n358_, new_n359_,
    new_n360_, new_n361_, new_n362_, new_n363_, new_n364_, new_n365_,
    new_n366_, new_n367_, new_n368_, new_n369_, new_n370_, new_n371_,
    new_n372_, new_n373_, new_n374_, new_n375_, new_n376_, new_n377_,
    new_n378_, new_n379_, new_n380_, new_n381_, new_n382_, new_n383_,
    new_n384_, new_n385_, new_n386_, new_n387_, new_n388_, new_n389_,
    new_n390_, new_n391_, new_n392_, new_n393_, new_n394_, new_n395_,
    new_n396_, new_n397_, new_n398_, new_n399_, new_n400_, new_n401_,
    new_n402_, new_n403_, new_n404_, new_n405_, new_n406_, new_n407_,
    new_n408_, new_n409_, new_n410_, new_n411_, new_n412_, new_n413_,
    new_n414_, new_n415_, new_n416_, new_n417_, new_n418_, new_n419_,
    new_n420_, new_n422_, new_n423_, new_n424_, new_n425_, new_n426_,
    new_n427_, new_n428_, new_n430_, new_n431_, new_n432_, new_n433_,
    new_n435_, new_n436_, new_n437_, new_n438_, new_n439_, new_n440_,
    new_n441_, new_n442_, new_n443_, new_n444_, new_n445_, new_n446_,
    new_n447_, new_n448_, new_n449_, new_n450_, new_n451_, new_n452_,
    new_n453_, new_n454_, new_n455_, new_n456_, new_n457_, new_n458_,
    new_n459_, new_n460_, new_n461_, new_n462_, new_n463_, new_n464_,
    new_n465_, new_n466_, new_n467_, new_n468_, new_n469_, new_n470_,
    new_n471_, new_n472_, new_n473_, new_n474_, new_n475_, new_n476_,
    new_n477_, new_n478_, new_n479_, new_n480_, new_n481_, new_n482_,
    new_n483_, new_n484_, new_n485_, new_n486_, new_n487_, new_n488_,
    new_n489_, new_n490_, new_n491_, new_n492_, new_n493_, new_n494_,
    new_n495_, new_n496_, new_n497_, new_n498_, new_n499_, new_n500_,
    new_n501_, new_n502_, new_n503_, new_n504_, new_n505_, new_n506_,
    new_n507_, new_n508_, new_n509_, new_n510_, new_n511_, new_n512_,
    new_n513_, new_n514_, new_n515_, new_n516_, new_n517_, new_n518_,
    new_n520_, new_n521_, new_n522_, new_n523_, new_n524_, new_n525_,
    new_n526_, new_n527_, new_n528_, new_n529_, new_n530_, new_n531_,
    new_n532_, new_n533_, new_n534_, new_n535_, new_n536_, new_n537_,
    new_n538_, new_n539_, new_n540_, new_n541_, new_n542_, new_n543_,
    new_n544_, new_n545_, new_n546_, new_n547_, new_n548_, new_n549_,
    new_n550_, new_n551_, new_n552_, new_n553_, new_n554_, new_n555_,
    new_n556_, new_n557_, new_n558_, new_n559_, new_n560_, new_n561_,
    new_n562_, new_n563_, new_n564_, new_n565_, new_n566_, new_n567_,
    new_n568_, new_n569_, new_n570_, new_n571_, new_n572_, new_n573_,
    new_n574_, new_n575_, new_n576_, new_n577_, new_n578_, new_n579_,
    new_n580_, new_n581_, new_n582_, new_n583_, new_n584_, new_n585_,
    new_n586_, new_n587_, new_n588_, new_n589_, new_n590_, new_n591_,
    new_n592_, new_n593_, new_n594_, new_n595_, new_n596_, new_n597_,
    new_n598_, new_n599_, new_n600_, new_n601_, new_n602_, new_n603_,
    new_n604_, new_n605_, new_n607_, new_n608_, new_n609_, new_n610_,
    new_n611_, new_n612_, new_n613_, new_n614_, new_n615_, new_n616_,
    new_n617_, new_n618_, new_n619_, new_n620_, new_n621_, new_n622_,
    new_n623_, new_n624_, new_n625_, new_n626_, new_n627_, new_n628_,
    new_n629_, new_n630_, new_n631_, new_n632_, new_n633_, new_n634_,
    new_n635_, new_n636_, new_n637_, new_n638_, new_n639_, new_n640_,
    new_n641_, new_n642_, new_n643_, new_n644_, new_n645_, new_n646_,
    new_n647_, new_n648_, new_n649_, new_n650_, new_n651_, new_n652_,
    new_n653_, new_n654_, new_n655_, new_n656_, new_n657_, new_n658_,
    new_n659_, new_n660_, new_n661_, new_n662_, new_n663_, new_n664_,
    new_n665_, new_n666_, new_n667_, new_n669_, new_n670_, new_n671_,
    new_n672_, new_n673_, new_n674_, new_n675_, new_n676_, new_n677_,
    new_n678_, new_n679_, new_n680_, new_n681_, new_n682_, new_n683_,
    new_n684_, new_n685_, new_n686_, new_n687_, new_n688_, new_n689_,
    new_n690_, new_n691_, new_n692_, new_n693_, new_n694_, new_n695_,
    new_n696_, new_n697_, new_n698_, new_n699_, new_n700_, new_n701_,
    new_n702_, new_n703_, new_n704_, new_n705_, new_n706_, new_n708_,
    new_n709_, new_n710_, new_n711_, new_n712_, new_n713_;
  assign new_n22_ = ~\totalcoeffs[3]  & ~\ctable[0] ;
  assign new_n23_ = ~\totalcoeffs[1]  & \trailingones[1] ;
  assign new_n24_ = ~\totalcoeffs[0]  & \trailingones[1] ;
  assign new_n25_ = \totalcoeffs[1]  & ~new_n24_;
  assign new_n26_ = ~new_n23_ & ~new_n25_;
  assign new_n27_ = new_n22_ & new_n26_;
  assign new_n28_ = \totalcoeffs[0]  & ~\trailingones[1] ;
  assign new_n29_ = ~\totalcoeffs[1]  & ~new_n28_;
  assign new_n30_ = \totalcoeffs[1]  & ~\trailingones[1] ;
  assign new_n31_ = ~\ctable[2]  & ~new_n30_;
  assign new_n32_ = ~new_n29_ & new_n31_;
  assign new_n33_ = ~new_n27_ & ~new_n32_;
  assign new_n34_ = ~\totalcoeffs[2]  & ~new_n33_;
  assign new_n35_ = ~\totalcoeffs[2]  & ~\ctable[0] ;
  assign new_n36_ = ~\totalcoeffs[0]  & ~new_n35_;
  assign new_n37_ = \totalcoeffs[1]  & \totalcoeffs[2] ;
  assign new_n38_ = ~new_n36_ & ~new_n37_;
  assign new_n39_ = ~\trailingones[1]  & ~new_n38_;
  assign new_n40_ = ~\totalcoeffs[2]  & ~\totalcoeffs[3] ;
  assign new_n41_ = \trailingones[1]  & ~new_n40_;
  assign new_n42_ = \totalcoeffs[0]  & \totalcoeffs[3] ;
  assign new_n43_ = ~new_n41_ & ~new_n42_;
  assign new_n44_ = ~\totalcoeffs[1]  & ~new_n43_;
  assign new_n45_ = \totalcoeffs[1]  & ~\totalcoeffs[3] ;
  assign new_n46_ = ~new_n44_ & ~new_n45_;
  assign new_n47_ = ~new_n39_ & new_n46_;
  assign new_n48_ = ~\ctable[2]  & ~new_n47_;
  assign new_n49_ = ~new_n34_ & ~new_n48_;
  assign new_n50_ = ~\trailingones[0]  & ~new_n49_;
  assign new_n51_ = \ctable[2]  & \trailingones[0] ;
  assign new_n52_ = ~\ctable[0]  & new_n51_;
  assign new_n53_ = ~\ctable[2]  & \trailingones[1] ;
  assign new_n54_ = ~new_n52_ & ~new_n53_;
  assign new_n55_ = \totalcoeffs[1]  & ~new_n54_;
  assign new_n56_ = \totalcoeffs[1]  & ~\ctable[2] ;
  assign new_n57_ = ~\ctable[0]  & ~\trailingones[1] ;
  assign new_n58_ = ~new_n56_ & new_n57_;
  assign new_n59_ = ~new_n55_ & ~new_n58_;
  assign new_n60_ = \totalcoeffs[0]  & ~\totalcoeffs[2] ;
  assign new_n61_ = ~new_n59_ & new_n60_;
  assign new_n62_ = \totalcoeffs[2]  & ~\trailingones[1] ;
  assign new_n63_ = ~\totalcoeffs[0]  & ~\totalcoeffs[1] ;
  assign new_n64_ = new_n62_ & new_n63_;
  assign new_n65_ = new_n52_ & new_n64_;
  assign new_n66_ = ~new_n61_ & ~new_n65_;
  assign new_n67_ = ~\totalcoeffs[3]  & ~new_n66_;
  assign new_n68_ = ~new_n50_ & ~new_n67_;
  assign new_n69_ = ~\ctable[1]  & ~new_n68_;
  assign new_n70_ = ~\totalcoeffs[0]  & ~\totalcoeffs[2] ;
  assign new_n71_ = new_n23_ & new_n70_;
  assign new_n72_ = ~\ctable[0]  & ~new_n71_;
  assign new_n73_ = \ctable[1]  & ~new_n72_;
  assign new_n74_ = ~\totalcoeffs[0]  & ~\trailingones[1] ;
  assign new_n75_ = \totalcoeffs[0]  & \trailingones[1] ;
  assign new_n76_ = ~new_n74_ & ~new_n75_;
  assign new_n77_ = \totalcoeffs[1]  & ~new_n76_;
  assign new_n78_ = \totalcoeffs[2]  & new_n77_;
  assign new_n79_ = \ctable[0]  & new_n78_;
  assign new_n80_ = ~new_n73_ & ~new_n79_;
  assign new_n81_ = \trailingones[0]  & ~new_n80_;
  assign new_n82_ = ~\totalcoeffs[1]  & ~new_n24_;
  assign new_n83_ = ~\trailingones[0]  & ~new_n82_;
  assign new_n84_ = ~\totalcoeffs[1]  & \totalcoeffs[2] ;
  assign new_n85_ = new_n28_ & new_n84_;
  assign new_n86_ = ~new_n83_ & ~new_n85_;
  assign new_n87_ = ~\ctable[0]  & ~new_n86_;
  assign new_n88_ = ~new_n81_ & ~new_n87_;
  assign new_n89_ = \totalcoeffs[3]  & ~new_n88_;
  assign new_n90_ = ~\totalcoeffs[2]  & ~new_n28_;
  assign new_n91_ = \ctable[1]  & ~new_n90_;
  assign new_n92_ = new_n40_ & new_n77_;
  assign new_n93_ = ~new_n91_ & ~new_n92_;
  assign new_n94_ = \ctable[0]  & ~new_n93_;
  assign new_n95_ = \totalcoeffs[2]  & \trailingones[1] ;
  assign new_n96_ = ~\totalcoeffs[2]  & new_n30_;
  assign new_n97_ = ~new_n95_ & ~new_n96_;
  assign new_n98_ = ~\totalcoeffs[0]  & ~\totalcoeffs[3] ;
  assign new_n99_ = ~new_n97_ & new_n98_;
  assign new_n100_ = \ctable[1]  & new_n99_;
  assign new_n101_ = ~new_n94_ & ~new_n100_;
  assign new_n102_ = \trailingones[0]  & ~new_n101_;
  assign new_n103_ = \totalcoeffs[2]  & ~\totalcoeffs[3] ;
  assign new_n104_ = new_n23_ & new_n103_;
  assign new_n105_ = \totalcoeffs[1]  & ~\trailingones[0] ;
  assign new_n106_ = ~new_n104_ & ~new_n105_;
  assign new_n107_ = ~\totalcoeffs[0]  & ~new_n106_;
  assign new_n108_ = ~\totalcoeffs[1]  & ~\trailingones[1] ;
  assign new_n109_ = ~\totalcoeffs[2]  & \ctable[1] ;
  assign new_n110_ = \totalcoeffs[3]  & ~new_n109_;
  assign new_n111_ = new_n108_ & ~new_n110_;
  assign new_n112_ = ~new_n95_ & ~new_n111_;
  assign new_n113_ = ~\trailingones[0]  & ~new_n112_;
  assign new_n114_ = ~new_n107_ & ~new_n113_;
  assign new_n115_ = ~\ctable[0]  & ~new_n114_;
  assign new_n116_ = ~\totalcoeffs[0]  & new_n40_;
  assign new_n117_ = ~\trailingones[0]  & new_n108_;
  assign new_n118_ = new_n116_ & new_n117_;
  assign new_n119_ = ~new_n115_ & ~new_n118_;
  assign new_n120_ = ~new_n102_ & new_n119_;
  assign new_n121_ = ~new_n89_ & new_n120_;
  assign new_n122_ = ~\ctable[2]  & ~new_n121_;
  assign new_n123_ = ~new_n69_ & ~new_n122_;
  assign new_n124_ = ~\totalcoeffs[4]  & ~new_n123_;
  assign new_n125_ = ~\trailingones[0]  & ~\trailingones[1] ;
  assign new_n126_ = ~\ctable[1]  & new_n125_;
  assign new_n127_ = \totalcoeffs[4]  & \trailingones[0] ;
  assign new_n128_ = \ctable[1]  & new_n127_;
  assign new_n129_ = ~new_n126_ & ~new_n128_;
  assign new_n130_ = \ctable[0]  & ~new_n129_;
  assign new_n131_ = \ctable[1]  & ~\trailingones[1] ;
  assign new_n132_ = \totalcoeffs[4]  & \trailingones[1] ;
  assign new_n133_ = ~new_n131_ & ~new_n132_;
  assign new_n134_ = \ctable[0]  & \ctable[1] ;
  assign new_n135_ = ~new_n133_ & ~new_n134_;
  assign new_n136_ = ~\trailingones[0]  & new_n135_;
  assign new_n137_ = ~new_n130_ & ~new_n136_;
  assign new_n138_ = ~\ctable[2]  & ~new_n137_;
  assign new_n139_ = ~\totalcoeffs[1]  & ~\totalcoeffs[3] ;
  assign new_n140_ = ~\totalcoeffs[2]  & new_n139_;
  assign new_n141_ = new_n138_ & new_n140_;
  assign new_n142_ = ~\totalcoeffs[0]  & new_n141_;
  assign \coeff_token[0]  = new_n124_ | new_n142_;
  assign new_n144_ = \totalcoeffs[0]  & \trailingones[0] ;
  assign new_n145_ = new_n95_ & new_n144_;
  assign new_n146_ = ~\totalcoeffs[2]  & ~\trailingones[0] ;
  assign new_n147_ = new_n74_ & new_n146_;
  assign new_n148_ = ~new_n145_ & ~new_n147_;
  assign new_n149_ = \ctable[0]  & ~new_n148_;
  assign new_n150_ = ~\ctable[0]  & \trailingones[0] ;
  assign new_n151_ = \ctable[1]  & \trailingones[1] ;
  assign new_n152_ = ~new_n150_ & ~new_n151_;
  assign new_n153_ = ~\totalcoeffs[0]  & ~new_n152_;
  assign new_n154_ = \trailingones[0]  & new_n151_;
  assign new_n155_ = ~\trailingones[0]  & new_n57_;
  assign new_n156_ = ~new_n154_ & ~new_n155_;
  assign new_n157_ = ~new_n153_ & new_n156_;
  assign new_n158_ = \totalcoeffs[2]  & ~new_n157_;
  assign new_n159_ = ~new_n149_ & ~new_n158_;
  assign new_n160_ = ~\totalcoeffs[4]  & ~new_n159_;
  assign new_n161_ = ~\ctable[1]  & \trailingones[1] ;
  assign new_n162_ = \ctable[0]  & ~\trailingones[0] ;
  assign new_n163_ = ~new_n127_ & ~new_n162_;
  assign new_n164_ = ~\ctable[1]  & ~new_n163_;
  assign new_n165_ = ~new_n132_ & ~new_n164_;
  assign new_n166_ = ~new_n161_ & ~new_n165_;
  assign new_n167_ = new_n70_ & new_n166_;
  assign new_n168_ = ~new_n160_ & ~new_n167_;
  assign new_n169_ = ~\totalcoeffs[1]  & ~new_n168_;
  assign new_n170_ = \ctable[1]  & \trailingones[0] ;
  assign new_n171_ = ~new_n152_ & ~new_n170_;
  assign new_n172_ = \totalcoeffs[0]  & new_n171_;
  assign new_n173_ = ~\totalcoeffs[0]  & \ctable[0] ;
  assign new_n174_ = ~\trailingones[0]  & \trailingones[1] ;
  assign new_n175_ = new_n173_ & new_n174_;
  assign new_n176_ = ~new_n172_ & ~new_n175_;
  assign new_n177_ = ~\totalcoeffs[2]  & ~new_n176_;
  assign new_n178_ = ~\ctable[1]  & ~\trailingones[0] ;
  assign new_n179_ = ~\totalcoeffs[0]  & \ctable[1] ;
  assign new_n180_ = ~\totalcoeffs[2]  & ~new_n179_;
  assign new_n181_ = new_n150_ & ~new_n180_;
  assign new_n182_ = ~new_n178_ & ~new_n181_;
  assign new_n183_ = ~\trailingones[1]  & ~new_n182_;
  assign new_n184_ = ~new_n177_ & ~new_n183_;
  assign new_n185_ = \totalcoeffs[1]  & ~new_n184_;
  assign new_n186_ = ~\ctable[1]  & \trailingones[0] ;
  assign new_n187_ = new_n62_ & new_n186_;
  assign new_n188_ = ~new_n185_ & ~new_n187_;
  assign new_n189_ = ~\totalcoeffs[4]  & ~new_n188_;
  assign new_n190_ = ~new_n169_ & ~new_n189_;
  assign new_n191_ = ~\totalcoeffs[3]  & ~new_n190_;
  assign new_n192_ = \ctable[0]  & new_n146_;
  assign new_n193_ = ~\totalcoeffs[3]  & ~\trailingones[0] ;
  assign new_n194_ = ~new_n150_ & ~new_n193_;
  assign new_n195_ = \totalcoeffs[0]  & new_n194_;
  assign new_n196_ = ~new_n192_ & ~new_n195_;
  assign new_n197_ = ~\totalcoeffs[1]  & ~new_n196_;
  assign new_n198_ = \totalcoeffs[3]  & \trailingones[0] ;
  assign new_n199_ = ~\totalcoeffs[2]  & ~new_n198_;
  assign new_n200_ = ~\totalcoeffs[0]  & ~new_n199_;
  assign new_n201_ = ~\totalcoeffs[2]  & \trailingones[0] ;
  assign new_n202_ = \totalcoeffs[0]  & new_n201_;
  assign new_n203_ = \totalcoeffs[0]  & ~\ctable[0] ;
  assign new_n204_ = ~new_n173_ & ~new_n203_;
  assign new_n205_ = ~new_n202_ & new_n204_;
  assign new_n206_ = \totalcoeffs[1]  & ~new_n205_;
  assign new_n207_ = ~new_n200_ & ~new_n206_;
  assign new_n208_ = ~new_n197_ & new_n207_;
  assign new_n209_ = ~\ctable[1]  & ~new_n208_;
  assign new_n210_ = ~\totalcoeffs[1]  & \ctable[1] ;
  assign new_n211_ = \totalcoeffs[2]  & ~new_n210_;
  assign new_n212_ = ~\totalcoeffs[1]  & ~\trailingones[0] ;
  assign new_n213_ = ~new_n211_ & ~new_n212_;
  assign new_n214_ = \totalcoeffs[3]  & new_n213_;
  assign new_n215_ = ~\totalcoeffs[0]  & \trailingones[0] ;
  assign new_n216_ = ~\totalcoeffs[1]  & ~\ctable[1] ;
  assign new_n217_ = \totalcoeffs[0]  & \totalcoeffs[1] ;
  assign new_n218_ = ~new_n216_ & ~new_n217_;
  assign new_n219_ = ~new_n215_ & new_n218_;
  assign new_n220_ = ~\totalcoeffs[2]  & new_n219_;
  assign new_n221_ = ~new_n214_ & ~new_n220_;
  assign new_n222_ = ~\ctable[0]  & ~new_n221_;
  assign new_n223_ = ~new_n209_ & ~new_n222_;
  assign new_n224_ = ~\trailingones[1]  & ~new_n223_;
  assign new_n225_ = \totalcoeffs[1]  & \ctable[0] ;
  assign new_n226_ = \totalcoeffs[3]  & ~\trailingones[0] ;
  assign new_n227_ = ~\totalcoeffs[1]  & ~\totalcoeffs[2] ;
  assign new_n228_ = new_n226_ & new_n227_;
  assign new_n229_ = ~new_n225_ & ~new_n228_;
  assign new_n230_ = \totalcoeffs[0]  & ~new_n229_;
  assign new_n231_ = \ctable[0]  & ~new_n40_;
  assign new_n232_ = \totalcoeffs[3]  & new_n37_;
  assign new_n233_ = ~new_n231_ & ~new_n232_;
  assign new_n234_ = ~new_n230_ & new_n233_;
  assign new_n235_ = \ctable[1]  & ~new_n234_;
  assign new_n236_ = new_n162_ & new_n232_;
  assign new_n237_ = ~new_n235_ & ~new_n236_;
  assign new_n238_ = \trailingones[1]  & ~new_n237_;
  assign new_n239_ = ~new_n224_ & ~new_n238_;
  assign new_n240_ = ~\totalcoeffs[4]  & ~new_n239_;
  assign new_n241_ = ~new_n191_ & ~new_n240_;
  assign new_n242_ = ~\ctable[2]  & ~new_n241_;
  assign new_n243_ = \totalcoeffs[2]  & ~new_n63_;
  assign new_n244_ = new_n90_ & ~new_n217_;
  assign new_n245_ = ~new_n243_ & ~new_n244_;
  assign new_n246_ = ~\trailingones[0]  & new_n245_;
  assign new_n247_ = new_n30_ & new_n201_;
  assign new_n248_ = ~new_n246_ & ~new_n247_;
  assign new_n249_ = \ctable[2]  & ~new_n248_;
  assign new_n250_ = ~new_n64_ & ~new_n249_;
  assign new_n251_ = ~\totalcoeffs[4]  & ~new_n250_;
  assign new_n252_ = ~\ctable[1]  & new_n251_;
  assign new_n253_ = new_n22_ & new_n252_;
  assign \coeff_token[1]  = new_n242_ | new_n253_;
  assign new_n255_ = ~\totalcoeffs[3]  & \trailingones[1] ;
  assign new_n256_ = ~new_n45_ & ~new_n174_;
  assign new_n257_ = ~new_n255_ & ~new_n256_;
  assign new_n258_ = ~\ctable[1]  & new_n257_;
  assign new_n259_ = \totalcoeffs[3]  & ~new_n201_;
  assign new_n260_ = \ctable[0]  & ~new_n259_;
  assign new_n261_ = \totalcoeffs[2]  & ~\ctable[0] ;
  assign new_n262_ = \totalcoeffs[3]  & ~new_n261_;
  assign new_n263_ = \trailingones[0]  & ~new_n262_;
  assign new_n264_ = ~new_n260_ & ~new_n263_;
  assign new_n265_ = \totalcoeffs[1]  & ~new_n264_;
  assign new_n266_ = ~\ctable[0]  & \ctable[1] ;
  assign new_n267_ = ~\trailingones[0]  & new_n266_;
  assign new_n268_ = new_n139_ & new_n267_;
  assign new_n269_ = ~new_n265_ & ~new_n268_;
  assign new_n270_ = ~\trailingones[1]  & ~new_n269_;
  assign new_n271_ = ~\totalcoeffs[1]  & ~new_n199_;
  assign new_n272_ = \totalcoeffs[2]  & ~new_n186_;
  assign new_n273_ = ~new_n271_ & ~new_n272_;
  assign new_n274_ = \ctable[0]  & ~new_n273_;
  assign new_n275_ = \totalcoeffs[1]  & \trailingones[0] ;
  assign new_n276_ = \ctable[1]  & ~new_n275_;
  assign new_n277_ = ~\trailingones[1]  & ~new_n276_;
  assign new_n278_ = ~\totalcoeffs[2]  & ~new_n277_;
  assign new_n279_ = ~\totalcoeffs[1]  & new_n174_;
  assign new_n280_ = ~new_n278_ & ~new_n279_;
  assign new_n281_ = \totalcoeffs[3]  & ~new_n280_;
  assign new_n282_ = \ctable[1]  & ~\trailingones[0] ;
  assign new_n283_ = \totalcoeffs[1]  & new_n255_;
  assign new_n284_ = new_n282_ & new_n283_;
  assign new_n285_ = ~new_n281_ & ~new_n284_;
  assign new_n286_ = ~new_n274_ & new_n285_;
  assign new_n287_ = ~new_n270_ & new_n286_;
  assign new_n288_ = ~new_n258_ & new_n287_;
  assign new_n289_ = ~\totalcoeffs[4]  & ~new_n288_;
  assign new_n290_ = \trailingones[0]  & ~\trailingones[1] ;
  assign new_n291_ = ~new_n178_ & ~new_n290_;
  assign new_n292_ = ~\ctable[0]  & new_n291_;
  assign new_n293_ = ~\totalcoeffs[3]  & \totalcoeffs[4] ;
  assign new_n294_ = ~\totalcoeffs[1]  & new_n293_;
  assign new_n295_ = ~new_n292_ & new_n294_;
  assign new_n296_ = ~\totalcoeffs[2]  & new_n295_;
  assign new_n297_ = ~new_n289_ & ~new_n296_;
  assign new_n298_ = ~\totalcoeffs[0]  & ~new_n297_;
  assign new_n299_ = \trailingones[0]  & new_n75_;
  assign new_n300_ = ~new_n125_ & ~new_n299_;
  assign new_n301_ = \ctable[0]  & ~new_n300_;
  assign new_n302_ = ~\ctable[0]  & new_n95_;
  assign new_n303_ = ~new_n301_ & ~new_n302_;
  assign new_n304_ = \totalcoeffs[1]  & ~new_n303_;
  assign new_n305_ = ~new_n174_ & ~new_n290_;
  assign new_n306_ = ~new_n108_ & new_n305_;
  assign new_n307_ = \totalcoeffs[2]  & ~new_n306_;
  assign new_n308_ = ~new_n304_ & ~new_n307_;
  assign new_n309_ = ~\totalcoeffs[3]  & ~new_n308_;
  assign new_n310_ = ~\totalcoeffs[1]  & \totalcoeffs[3] ;
  assign new_n311_ = \ctable[0]  & ~new_n310_;
  assign new_n312_ = ~\totalcoeffs[2]  & new_n125_;
  assign new_n313_ = ~new_n311_ & new_n312_;
  assign new_n314_ = ~\totalcoeffs[1]  & \trailingones[0] ;
  assign new_n315_ = new_n41_ & new_n314_;
  assign new_n316_ = ~new_n313_ & ~new_n315_;
  assign new_n317_ = \totalcoeffs[0]  & ~new_n316_;
  assign new_n318_ = ~new_n309_ & ~new_n317_;
  assign new_n319_ = ~\ctable[1]  & ~new_n318_;
  assign new_n320_ = \totalcoeffs[1]  & \trailingones[1] ;
  assign new_n321_ = \totalcoeffs[2]  & new_n320_;
  assign new_n322_ = ~new_n314_ & ~new_n321_;
  assign new_n323_ = \ctable[1]  & ~new_n322_;
  assign new_n324_ = \trailingones[0]  & ~new_n62_;
  assign new_n325_ = \totalcoeffs[2]  & new_n125_;
  assign new_n326_ = ~new_n324_ & ~new_n325_;
  assign new_n327_ = ~new_n323_ & new_n326_;
  assign new_n328_ = \totalcoeffs[3]  & ~new_n327_;
  assign new_n329_ = \ctable[1]  & ~new_n23_;
  assign new_n330_ = ~new_n30_ & ~new_n329_;
  assign new_n331_ = \trailingones[0]  & ~new_n330_;
  assign new_n332_ = ~new_n108_ & ~new_n320_;
  assign new_n333_ = new_n193_ & ~new_n332_;
  assign new_n334_ = ~new_n331_ & ~new_n333_;
  assign new_n335_ = ~\totalcoeffs[2]  & ~new_n334_;
  assign new_n336_ = ~new_n328_ & ~new_n335_;
  assign new_n337_ = new_n203_ & ~new_n336_;
  assign new_n338_ = ~new_n319_ & ~new_n337_;
  assign new_n339_ = ~\totalcoeffs[4]  & ~new_n338_;
  assign new_n340_ = ~new_n298_ & ~new_n339_;
  assign new_n341_ = ~\ctable[2]  & ~new_n340_;
  assign new_n342_ = ~\ctable[0]  & ~\ctable[1] ;
  assign new_n343_ = new_n51_ & new_n75_;
  assign new_n344_ = ~new_n74_ & ~new_n343_;
  assign new_n345_ = \totalcoeffs[1]  & ~new_n344_;
  assign new_n346_ = new_n28_ & new_n212_;
  assign new_n347_ = ~new_n345_ & ~new_n346_;
  assign new_n348_ = ~\totalcoeffs[4]  & ~new_n347_;
  assign new_n349_ = new_n40_ & new_n348_;
  assign new_n350_ = new_n342_ & new_n349_;
  assign \coeff_token[2]  = new_n341_ | new_n350_;
  assign new_n352_ = \totalcoeffs[3]  & ~new_n161_;
  assign new_n353_ = \totalcoeffs[2]  & \ctable[1] ;
  assign new_n354_ = ~new_n352_ & ~new_n353_;
  assign new_n355_ = ~\totalcoeffs[4]  & ~new_n354_;
  assign new_n356_ = \trailingones[0]  & \trailingones[1] ;
  assign new_n357_ = new_n342_ & new_n356_;
  assign new_n358_ = ~new_n134_ & ~new_n357_;
  assign new_n359_ = ~\totalcoeffs[2]  & new_n293_;
  assign new_n360_ = ~new_n358_ & new_n359_;
  assign new_n361_ = ~new_n355_ & ~new_n360_;
  assign new_n362_ = ~\totalcoeffs[1]  & ~new_n361_;
  assign new_n363_ = \ctable[0]  & \trailingones[0] ;
  assign new_n364_ = new_n161_ & new_n363_;
  assign new_n365_ = ~new_n155_ & ~new_n364_;
  assign new_n366_ = \totalcoeffs[2]  & ~new_n365_;
  assign new_n367_ = \ctable[0]  & ~new_n186_;
  assign new_n368_ = \totalcoeffs[3]  & ~new_n367_;
  assign new_n369_ = ~new_n267_ & ~new_n368_;
  assign new_n370_ = ~new_n366_ & new_n369_;
  assign new_n371_ = \totalcoeffs[1]  & ~new_n370_;
  assign new_n372_ = \totalcoeffs[2]  & new_n266_;
  assign new_n373_ = ~new_n371_ & ~new_n372_;
  assign new_n374_ = ~\totalcoeffs[4]  & ~new_n373_;
  assign new_n375_ = ~new_n362_ & ~new_n374_;
  assign new_n376_ = ~\totalcoeffs[0]  & ~new_n375_;
  assign new_n377_ = \totalcoeffs[2]  & ~new_n194_;
  assign new_n378_ = ~\totalcoeffs[2]  & new_n363_;
  assign new_n379_ = ~new_n377_ & ~new_n378_;
  assign new_n380_ = ~\trailingones[1]  & ~new_n379_;
  assign new_n381_ = \ctable[0]  & \trailingones[1] ;
  assign new_n382_ = ~\trailingones[0]  & new_n381_;
  assign new_n383_ = ~\totalcoeffs[3]  & ~new_n382_;
  assign new_n384_ = ~\totalcoeffs[2]  & ~new_n383_;
  assign new_n385_ = ~\ctable[1]  & ~new_n226_;
  assign new_n386_ = \totalcoeffs[3]  & ~\ctable[0] ;
  assign new_n387_ = ~new_n385_ & ~new_n386_;
  assign new_n388_ = ~new_n384_ & ~new_n387_;
  assign new_n389_ = ~new_n380_ & new_n388_;
  assign new_n390_ = \totalcoeffs[1]  & ~new_n389_;
  assign new_n391_ = ~\totalcoeffs[3]  & new_n266_;
  assign new_n392_ = new_n192_ & new_n216_;
  assign new_n393_ = ~new_n391_ & ~new_n392_;
  assign new_n394_ = ~\trailingones[1]  & ~new_n393_;
  assign new_n395_ = ~new_n390_ & ~new_n394_;
  assign new_n396_ = \totalcoeffs[0]  & ~new_n395_;
  assign new_n397_ = ~new_n40_ & new_n266_;
  assign new_n398_ = \totalcoeffs[3]  & ~\ctable[1] ;
  assign new_n399_ = \totalcoeffs[2]  & new_n398_;
  assign new_n400_ = ~new_n397_ & ~new_n399_;
  assign new_n401_ = \trailingones[1]  & ~new_n400_;
  assign new_n402_ = ~\trailingones[1]  & new_n266_;
  assign new_n403_ = ~new_n398_ & ~new_n402_;
  assign new_n404_ = ~\trailingones[0]  & ~new_n403_;
  assign new_n405_ = ~new_n401_ & ~new_n404_;
  assign new_n406_ = ~\totalcoeffs[1]  & ~new_n405_;
  assign new_n407_ = ~new_n57_ & ~new_n178_;
  assign new_n408_ = ~\totalcoeffs[2]  & ~new_n407_;
  assign new_n409_ = ~\ctable[1]  & ~new_n381_;
  assign new_n410_ = ~new_n320_ & ~new_n363_;
  assign new_n411_ = new_n409_ & ~new_n410_;
  assign new_n412_ = ~new_n408_ & ~new_n411_;
  assign new_n413_ = \totalcoeffs[3]  & ~new_n412_;
  assign new_n414_ = \totalcoeffs[1]  & new_n290_;
  assign new_n415_ = new_n266_ & new_n414_;
  assign new_n416_ = ~new_n413_ & ~new_n415_;
  assign new_n417_ = ~new_n406_ & new_n416_;
  assign new_n418_ = ~new_n396_ & new_n417_;
  assign new_n419_ = ~\totalcoeffs[4]  & ~new_n418_;
  assign new_n420_ = ~new_n376_ & ~new_n419_;
  assign \coeff_token[3]  = ~\ctable[2]  & ~new_n420_;
  assign new_n422_ = ~\totalcoeffs[4]  & new_n243_;
  assign new_n423_ = \totalcoeffs[3]  & ~\totalcoeffs[4] ;
  assign new_n424_ = ~new_n293_ & ~new_n423_;
  assign new_n425_ = ~\totalcoeffs[0]  & new_n227_;
  assign new_n426_ = ~new_n424_ & new_n425_;
  assign new_n427_ = ~new_n422_ & ~new_n426_;
  assign new_n428_ = ~\ctable[2]  & ~new_n427_;
  assign \coeff_token[4]  = new_n134_ & new_n428_;
  assign new_n430_ = new_n63_ & new_n359_;
  assign new_n431_ = new_n423_ & ~new_n425_;
  assign new_n432_ = ~new_n430_ & ~new_n431_;
  assign new_n433_ = ~\ctable[2]  & ~new_n432_;
  assign \coeff_token[5]  = new_n134_ & new_n433_;
  assign new_n435_ = ~\totalcoeffs[1]  & ~\ctable[0] ;
  assign new_n436_ = \totalcoeffs[2]  & ~new_n435_;
  assign new_n437_ = ~\trailingones[1]  & ~new_n436_;
  assign new_n438_ = ~\ctable[1]  & new_n437_;
  assign new_n439_ = \ctable[0]  & new_n320_;
  assign new_n440_ = ~new_n438_ & ~new_n439_;
  assign new_n441_ = \totalcoeffs[0]  & ~new_n440_;
  assign new_n442_ = ~\totalcoeffs[0]  & ~new_n57_;
  assign new_n443_ = \totalcoeffs[2]  & new_n442_;
  assign new_n444_ = ~new_n441_ & ~new_n443_;
  assign new_n445_ = \trailingones[0]  & ~new_n444_;
  assign new_n446_ = \totalcoeffs[2]  & new_n24_;
  assign new_n447_ = ~new_n117_ & ~new_n446_;
  assign new_n448_ = \ctable[0]  & ~new_n447_;
  assign new_n449_ = ~new_n445_ & ~new_n448_;
  assign new_n450_ = ~new_n125_ & ~new_n356_;
  assign new_n451_ = \ctable[1]  & ~new_n450_;
  assign new_n452_ = ~\totalcoeffs[2]  & \trailingones[1] ;
  assign new_n453_ = ~new_n62_ & ~new_n452_;
  assign new_n454_ = new_n451_ & new_n453_;
  assign new_n455_ = new_n449_ & ~new_n454_;
  assign new_n456_ = ~\ctable[2]  & ~new_n455_;
  assign new_n457_ = \ctable[2]  & ~\trailingones[1] ;
  assign new_n458_ = \trailingones[0]  & ~new_n457_;
  assign new_n459_ = new_n84_ & ~new_n458_;
  assign new_n460_ = ~new_n96_ & ~new_n459_;
  assign new_n461_ = ~\totalcoeffs[0]  & ~new_n460_;
  assign new_n462_ = new_n144_ & new_n320_;
  assign new_n463_ = ~new_n125_ & ~new_n462_;
  assign new_n464_ = \ctable[2]  & ~new_n463_;
  assign new_n465_ = ~\totalcoeffs[2]  & new_n464_;
  assign new_n466_ = ~new_n461_ & ~new_n465_;
  assign new_n467_ = new_n342_ & ~new_n466_;
  assign new_n468_ = ~new_n456_ & ~new_n467_;
  assign new_n469_ = ~\totalcoeffs[3]  & ~new_n468_;
  assign new_n470_ = ~new_n117_ & ~new_n320_;
  assign new_n471_ = \totalcoeffs[0]  & ~new_n470_;
  assign new_n472_ = \totalcoeffs[2]  & new_n30_;
  assign new_n473_ = ~new_n471_ & ~new_n472_;
  assign new_n474_ = ~\totalcoeffs[0]  & ~\ctable[1] ;
  assign new_n475_ = ~new_n212_ & new_n332_;
  assign new_n476_ = new_n474_ & new_n475_;
  assign new_n477_ = new_n473_ & ~new_n476_;
  assign new_n478_ = ~\ctable[0]  & ~new_n477_;
  assign new_n479_ = ~\trailingones[0]  & new_n217_;
  assign new_n480_ = \totalcoeffs[0]  & new_n170_;
  assign new_n481_ = ~new_n105_ & ~new_n480_;
  assign new_n482_ = ~\totalcoeffs[2]  & ~new_n481_;
  assign new_n483_ = ~new_n479_ & ~new_n482_;
  assign new_n484_ = \trailingones[1]  & ~new_n483_;
  assign new_n485_ = ~\totalcoeffs[0]  & ~\trailingones[0] ;
  assign new_n486_ = ~new_n203_ & ~new_n485_;
  assign new_n487_ = new_n30_ & new_n486_;
  assign new_n488_ = ~new_n484_ & ~new_n487_;
  assign new_n489_ = ~new_n478_ & new_n488_;
  assign new_n490_ = \totalcoeffs[3]  & ~new_n489_;
  assign new_n491_ = ~\totalcoeffs[2]  & \ctable[0] ;
  assign new_n492_ = ~new_n76_ & new_n491_;
  assign new_n493_ = ~\ctable[1]  & ~new_n261_;
  assign new_n494_ = new_n24_ & ~new_n493_;
  assign new_n495_ = ~new_n492_ & ~new_n494_;
  assign new_n496_ = ~\trailingones[0]  & ~new_n495_;
  assign new_n497_ = \totalcoeffs[2]  & ~new_n125_;
  assign new_n498_ = ~new_n299_ & ~new_n497_;
  assign new_n499_ = \ctable[1]  & ~new_n498_;
  assign new_n500_ = ~new_n496_ & ~new_n499_;
  assign new_n501_ = \totalcoeffs[1]  & ~new_n500_;
  assign new_n502_ = ~\trailingones[0]  & ~new_n474_;
  assign new_n503_ = ~new_n203_ & ~new_n502_;
  assign new_n504_ = ~\trailingones[1]  & ~new_n503_;
  assign new_n505_ = ~\totalcoeffs[2]  & new_n504_;
  assign new_n506_ = \totalcoeffs[2]  & \trailingones[0] ;
  assign new_n507_ = new_n24_ & new_n506_;
  assign new_n508_ = ~new_n505_ & ~new_n507_;
  assign new_n509_ = ~\totalcoeffs[1]  & ~new_n508_;
  assign new_n510_ = ~new_n501_ & ~new_n509_;
  assign new_n511_ = ~new_n490_ & new_n510_;
  assign new_n512_ = ~\ctable[2]  & ~new_n511_;
  assign new_n513_ = ~new_n469_ & ~new_n512_;
  assign new_n514_ = ~\totalcoeffs[4]  & ~new_n513_;
  assign new_n515_ = ~\totalcoeffs[1]  & \totalcoeffs[4] ;
  assign new_n516_ = new_n116_ & new_n515_;
  assign new_n517_ = ~new_n134_ & ~new_n516_;
  assign new_n518_ = ~\ctable[2]  & ~new_n517_;
  assign \ctoken_len[0]  = ~new_n514_ & ~new_n518_;
  assign new_n520_ = ~\totalcoeffs[3]  & \trailingones[0] ;
  assign new_n521_ = ~new_n151_ & ~new_n520_;
  assign new_n522_ = \totalcoeffs[0]  & ~new_n521_;
  assign new_n523_ = new_n215_ & new_n398_;
  assign new_n524_ = ~new_n282_ & ~new_n523_;
  assign new_n525_ = \trailingones[1]  & ~new_n524_;
  assign new_n526_ = ~\trailingones[1]  & new_n170_;
  assign new_n527_ = ~new_n525_ & ~new_n526_;
  assign new_n528_ = ~new_n522_ & new_n527_;
  assign new_n529_ = ~\totalcoeffs[2]  & ~new_n528_;
  assign new_n530_ = ~\totalcoeffs[3]  & new_n356_;
  assign new_n531_ = \totalcoeffs[3]  & ~new_n356_;
  assign new_n532_ = ~new_n144_ & ~new_n531_;
  assign new_n533_ = ~\ctable[1]  & ~new_n532_;
  assign new_n534_ = ~new_n530_ & ~new_n533_;
  assign new_n535_ = \totalcoeffs[2]  & ~new_n534_;
  assign new_n536_ = ~\totalcoeffs[3]  & new_n126_;
  assign new_n537_ = ~new_n535_ & ~new_n536_;
  assign new_n538_ = ~new_n529_ & new_n537_;
  assign new_n539_ = \totalcoeffs[1]  & ~new_n538_;
  assign new_n540_ = ~new_n74_ & ~new_n174_;
  assign new_n541_ = ~\ctable[1]  & ~new_n540_;
  assign new_n542_ = ~\totalcoeffs[2]  & new_n541_;
  assign new_n543_ = ~\totalcoeffs[0]  & new_n451_;
  assign new_n544_ = ~new_n542_ & ~new_n543_;
  assign new_n545_ = \totalcoeffs[3]  & ~new_n544_;
  assign new_n546_ = ~\totalcoeffs[0]  & new_n146_;
  assign new_n547_ = ~new_n480_ & ~new_n546_;
  assign new_n548_ = ~\trailingones[1]  & ~new_n547_;
  assign new_n549_ = ~\ctable[1]  & ~new_n193_;
  assign new_n550_ = new_n497_ & ~new_n549_;
  assign new_n551_ = ~new_n548_ & ~new_n550_;
  assign new_n552_ = ~new_n545_ & new_n551_;
  assign new_n553_ = ~\totalcoeffs[1]  & ~new_n552_;
  assign new_n554_ = ~\totalcoeffs[2]  & \totalcoeffs[3] ;
  assign new_n555_ = ~\trailingones[1]  & new_n282_;
  assign new_n556_ = new_n554_ & new_n555_;
  assign new_n557_ = ~new_n553_ & ~new_n556_;
  assign new_n558_ = ~new_n539_ & new_n557_;
  assign new_n559_ = ~\ctable[0]  & ~new_n558_;
  assign new_n560_ = \totalcoeffs[0]  & ~new_n453_;
  assign new_n561_ = \ctable[0]  & ~\trailingones[1] ;
  assign new_n562_ = ~\totalcoeffs[0]  & new_n561_;
  assign new_n563_ = ~new_n560_ & ~new_n562_;
  assign new_n564_ = \trailingones[0]  & ~new_n563_;
  assign new_n565_ = new_n95_ & new_n162_;
  assign new_n566_ = ~new_n564_ & ~new_n565_;
  assign new_n567_ = ~\totalcoeffs[3]  & ~new_n566_;
  assign new_n568_ = \totalcoeffs[3]  & \ctable[0] ;
  assign new_n569_ = ~new_n62_ & ~new_n568_;
  assign new_n570_ = ~\totalcoeffs[0]  & ~new_n569_;
  assign new_n571_ = \totalcoeffs[3]  & new_n491_;
  assign new_n572_ = ~new_n570_ & ~new_n571_;
  assign new_n573_ = ~\trailingones[0]  & ~new_n572_;
  assign new_n574_ = new_n554_ & new_n561_;
  assign new_n575_ = ~new_n573_ & ~new_n574_;
  assign new_n576_ = ~new_n567_ & new_n575_;
  assign new_n577_ = \totalcoeffs[1]  & ~new_n576_;
  assign new_n578_ = \totalcoeffs[2]  & \totalcoeffs[3] ;
  assign new_n579_ = ~\totalcoeffs[2]  & ~new_n42_;
  assign new_n580_ = ~new_n450_ & ~new_n579_;
  assign new_n581_ = ~new_n578_ & ~new_n580_;
  assign new_n582_ = \ctable[0]  & ~new_n581_;
  assign new_n583_ = new_n42_ & new_n325_;
  assign new_n584_ = ~new_n582_ & ~new_n583_;
  assign new_n585_ = ~\totalcoeffs[1]  & ~new_n584_;
  assign new_n586_ = \trailingones[0]  & new_n381_;
  assign new_n587_ = new_n578_ & new_n586_;
  assign new_n588_ = ~new_n585_ & ~new_n587_;
  assign new_n589_ = ~new_n577_ & new_n588_;
  assign new_n590_ = ~\ctable[1]  & ~new_n589_;
  assign new_n591_ = ~new_n559_ & ~new_n590_;
  assign new_n592_ = ~\ctable[2]  & ~new_n591_;
  assign new_n593_ = \totalcoeffs[2]  & ~new_n305_;
  assign new_n594_ = ~\totalcoeffs[0]  & new_n593_;
  assign new_n595_ = ~\trailingones[1]  & new_n51_;
  assign new_n596_ = new_n60_ & new_n595_;
  assign new_n597_ = ~new_n594_ & ~new_n596_;
  assign new_n598_ = new_n216_ & ~new_n597_;
  assign new_n599_ = new_n22_ & new_n598_;
  assign new_n600_ = ~new_n592_ & ~new_n599_;
  assign new_n601_ = ~\totalcoeffs[4]  & ~new_n600_;
  assign new_n602_ = new_n35_ & new_n98_;
  assign new_n603_ = \totalcoeffs[4]  & ~\ctable[2] ;
  assign new_n604_ = new_n216_ & new_n603_;
  assign new_n605_ = new_n602_ & new_n604_;
  assign \ctoken_len[1]  = ~new_n601_ & ~new_n605_;
  assign new_n607_ = new_n227_ & new_n561_;
  assign new_n608_ = ~new_n283_ & ~new_n607_;
  assign new_n609_ = ~\totalcoeffs[0]  & ~new_n608_;
  assign new_n610_ = ~\totalcoeffs[1]  & \ctable[0] ;
  assign new_n611_ = ~new_n22_ & ~new_n610_;
  assign new_n612_ = ~new_n108_ & ~new_n255_;
  assign new_n613_ = ~new_n611_ & new_n612_;
  assign new_n614_ = ~\totalcoeffs[2]  & new_n613_;
  assign new_n615_ = new_n332_ & ~new_n435_;
  assign new_n616_ = new_n103_ & ~new_n615_;
  assign new_n617_ = ~new_n614_ & ~new_n616_;
  assign new_n618_ = ~new_n609_ & new_n617_;
  assign new_n619_ = ~\trailingones[0]  & ~new_n618_;
  assign new_n620_ = ~new_n98_ & ~new_n611_;
  assign new_n621_ = ~\totalcoeffs[2]  & new_n620_;
  assign new_n622_ = new_n139_ & new_n203_;
  assign new_n623_ = ~new_n621_ & ~new_n622_;
  assign new_n624_ = \trailingones[0]  & ~new_n623_;
  assign new_n625_ = ~\ctable[0]  & ~new_n215_;
  assign new_n626_ = ~new_n568_ & ~new_n625_;
  assign new_n627_ = new_n37_ & new_n626_;
  assign new_n628_ = ~new_n624_ & ~new_n627_;
  assign new_n629_ = ~\trailingones[1]  & ~new_n628_;
  assign new_n630_ = ~new_n261_ & ~new_n568_;
  assign new_n631_ = ~new_n259_ & ~new_n630_;
  assign new_n632_ = \totalcoeffs[1]  & new_n631_;
  assign new_n633_ = ~new_n173_ & new_n310_;
  assign new_n634_ = new_n201_ & new_n633_;
  assign new_n635_ = ~new_n632_ & ~new_n634_;
  assign new_n636_ = \trailingones[1]  & ~new_n635_;
  assign new_n637_ = ~new_n629_ & ~new_n636_;
  assign new_n638_ = ~new_n619_ & new_n637_;
  assign new_n639_ = ~\ctable[1]  & ~new_n638_;
  assign new_n640_ = ~\totalcoeffs[1]  & ~new_n125_;
  assign new_n641_ = \totalcoeffs[2]  & ~new_n640_;
  assign new_n642_ = ~new_n329_ & ~new_n641_;
  assign new_n643_ = \totalcoeffs[0]  & ~new_n642_;
  assign new_n644_ = ~\ctable[1]  & ~new_n105_;
  assign new_n645_ = \totalcoeffs[2]  & ~new_n644_;
  assign new_n646_ = \trailingones[0]  & ~new_n30_;
  assign new_n647_ = new_n329_ & ~new_n646_;
  assign new_n648_ = ~new_n645_ & ~new_n647_;
  assign new_n649_ = ~new_n643_ & new_n648_;
  assign new_n650_ = new_n386_ & ~new_n649_;
  assign new_n651_ = ~new_n639_ & ~new_n650_;
  assign new_n652_ = ~\ctable[2]  & ~new_n651_;
  assign new_n653_ = ~new_n146_ & ~new_n506_;
  assign new_n654_ = ~\totalcoeffs[0]  & ~new_n653_;
  assign new_n655_ = ~new_n202_ & ~new_n654_;
  assign new_n656_ = ~\trailingones[1]  & ~new_n655_;
  assign new_n657_ = new_n95_ & new_n485_;
  assign new_n658_ = ~new_n656_ & ~new_n657_;
  assign new_n659_ = ~\totalcoeffs[1]  & ~new_n658_;
  assign new_n660_ = new_n320_ & new_n546_;
  assign new_n661_ = ~new_n659_ & ~new_n660_;
  assign new_n662_ = new_n22_ & ~new_n661_;
  assign new_n663_ = ~\ctable[1]  & new_n662_;
  assign new_n664_ = ~new_n652_ & ~new_n663_;
  assign new_n665_ = ~\totalcoeffs[4]  & ~new_n664_;
  assign new_n666_ = new_n22_ & new_n603_;
  assign new_n667_ = new_n425_ & new_n666_;
  assign \ctoken_len[2]  = ~new_n665_ & ~new_n667_;
  assign new_n669_ = \totalcoeffs[4]  & ~new_n140_;
  assign new_n670_ = new_n203_ & new_n399_;
  assign new_n671_ = ~\ctable[2]  & ~new_n670_;
  assign new_n672_ = ~new_n640_ & ~new_n671_;
  assign new_n673_ = ~\ctable[2]  & ~new_n140_;
  assign new_n674_ = \totalcoeffs[0]  & ~new_n673_;
  assign new_n675_ = \ctable[2]  & ~new_n103_;
  assign new_n676_ = ~\totalcoeffs[3]  & ~new_n57_;
  assign new_n677_ = \totalcoeffs[3]  & ~new_n151_;
  assign new_n678_ = new_n215_ & ~new_n677_;
  assign new_n679_ = ~new_n676_ & ~new_n678_;
  assign new_n680_ = ~\totalcoeffs[2]  & ~new_n679_;
  assign new_n681_ = ~new_n356_ & new_n399_;
  assign new_n682_ = ~\ctable[0]  & new_n681_;
  assign new_n683_ = ~\ctable[1]  & ~new_n586_;
  assign new_n684_ = ~\totalcoeffs[3]  & ~new_n683_;
  assign new_n685_ = ~new_n682_ & ~new_n684_;
  assign new_n686_ = ~new_n680_ & new_n685_;
  assign new_n687_ = \totalcoeffs[1]  & ~new_n686_;
  assign new_n688_ = new_n215_ & ~new_n409_;
  assign new_n689_ = ~new_n151_ & ~new_n688_;
  assign new_n690_ = \totalcoeffs[3]  & ~new_n689_;
  assign new_n691_ = \totalcoeffs[4]  & ~new_n342_;
  assign new_n692_ = ~\totalcoeffs[3]  & ~new_n691_;
  assign new_n693_ = ~new_n690_ & ~new_n692_;
  assign new_n694_ = ~\totalcoeffs[2]  & ~new_n693_;
  assign new_n695_ = ~\trailingones[0]  & ~new_n381_;
  assign new_n696_ = new_n676_ & ~new_n695_;
  assign new_n697_ = \totalcoeffs[2]  & new_n696_;
  assign new_n698_ = ~new_n694_ & ~new_n697_;
  assign new_n699_ = ~\totalcoeffs[1]  & ~new_n698_;
  assign new_n700_ = ~\ctable[0]  & ~new_n103_;
  assign new_n701_ = \ctable[1]  & ~new_n700_;
  assign new_n702_ = ~new_n699_ & ~new_n701_;
  assign new_n703_ = ~new_n687_ & new_n702_;
  assign new_n704_ = ~new_n675_ & new_n703_;
  assign new_n705_ = ~new_n674_ & new_n704_;
  assign new_n706_ = ~new_n672_ & new_n705_;
  assign \ctoken_len[3]  = ~new_n669_ & new_n706_;
  assign new_n708_ = ~\trailingones[0]  & ~new_n29_;
  assign new_n709_ = ~new_n25_ & ~new_n708_;
  assign new_n710_ = new_n423_ & ~new_n709_;
  assign new_n711_ = \totalcoeffs[2]  & new_n710_;
  assign new_n712_ = ~new_n430_ & ~new_n711_;
  assign new_n713_ = ~\ctable[2]  & ~new_n712_;
  assign \ctoken_len[4]  = new_n342_ & new_n713_;
endmodule


