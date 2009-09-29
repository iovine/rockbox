static sample_t a52_imdct_window[256]ICONST_ATTR={
				       146020,261886,393529,545197,719447,918478,1144416,1399394,1685589,2005234,2360623,2754115,3188134,3665170,4187773,4758556, 5380193,6055411,6786995,7577779,8430645,9348521,10334375,11391212,12522071,13730020,15018150,16389576,17847424,19394833,21034947,22770912, 24605865,26542938,28585242,30735872,32997891,35374332,37868188,40482408,43219889,46083473,49075937,52199993,55458273,58853331,62387636,66063559, 69883377,73849259,77963266,82227341,86643307,91212859,95937560,100818835,105857968,111056092,116414194,121933098,127613474,133455822,139460477,145627601, 151957182,158449029,165102772,171917855,178893540,186028900,193322822,200774000,208380940,216141958,224055176,232118527,240329753,248686407,257185854,265825270, 274601649,283511802,292552357,301719768,311010314,320420105,329945084,339581031,349323572,359168178,369110174,379144743,389266934,399471665,409753732,420107815, 430528483,441010205,451547355,462134219,472765003,483433845,494134818,504861939,515609181,526370480,537139740,547910849,558677680,569434108,580174011,590891284, 601579849,612233658,622846709,633413050,643926788,654382103,664773249,675094567,685340494,695505569,705584441,715571877,725462772,735252152,744935184,754507184, 763963620,773300119,782512477,791596659,800548807,809365245,818042484,826577226,834966364,843206992,851296404,859232096,867011771,874633340,882094922,889394844, 896531647,903504079,910311101,916951881,923425798,929732436,935871584,941843233,947647575,953284997,958756080,964061593,969202490,974179906,978995149,983649698, 988145195,992483442,996666390,1000696136,1004574919,1008305104,1011889185,1015329772,1018629583,1021791439,1024818257,1027713038,1030478862,1033118881,1035636308,1038034411, 1040316504,1042485942,1044546109,1046500412,1048352275,1050105129,1051762405,1053327531,1054803917,1056194958,1057504020,1058734435,1059889501,1060972468,1061986539,1062934861, 1063820523,1064646551,1065415903,1066131467,1066796055,1067412403,1067983168,1068510924,1068998160,1069447282,1069860607,1070240366,1070588702,1070907668,1071199230,1071465266, 1071707567,1071927836,1072127692,1072308670,1072472221,1072619716,1072752449,1072871635,1072978415,1073073858,1073158963,1073234663,1073301826,1073361257,1073413702,1073459852, 1073500344,1073535763,1073566646,1073593486,1073616731,1073636791,1073654036,1073668804,1073681398,1073692090,1073701126,1073708726,1073715084,1073720373,1073724748,1073728344, 1073731279,1073733657,1073735568,1073737090,1073738291,1073739229,1073739951,1073740500,1073740912,1073741214,1073741431,1073741582,1073741685,1073741751,1073741792,1073741814
};

static sample_t roots16[3]ICONST_ATTR={992008094,759250124,410903206};
static sample_t roots32[7]ICONST_ATTR={1053110175,992008094,892783698,759250124,596538995,410903206,209476638};
static sample_t roots64[15]ICONST_ATTR={1068571463,1053110175,1027506861,992008094,946955747,892783698,830013654,759250124,681174602,596538995,506158392,410903206,311690798,209476638,105245103};
static sample_t roots128[31]ICONST_ATTR={1072448454,1068571463,1062120190,1053110175,1041563127,1027506861,1010975241,992008094,970651112,946955747,920979082,892783698,862437519,830013654,795590212,759250124,721080937,681174602,639627257,596538995,552013618,506158392,459083785,410903206,361732725,311690798,260897981,209476638,157550647,105245103,52686014};

static complex_t pre1[128]ICONST_ATTR={{761575898,756917205},{3294193,1073736770},{413944710,990742792},{-407857834,993264059},{599275209,890949340},{-206244755,1053747885},{-593797166,894609652},{212706548,1052462554},{683717842,827919933},{-101966276,1068889322},{314841678,1026545772},{-503250790,948504162},{-678624950,832099562},{108522938,1068243547},{509061229,945398418},{-308536985,1028458279},{723518379,793374223},{-49395540,1072605046},{364832651,1009860703},{-456103709,972054993},{554836544,919281193},{-257701283,1042358649},{-636978326,864395809},{160808444,1061631832},{-718636707,797798713},{55975991,1072281769},{462059540,969238095},{-358629394,1012080264},{642270168,860471112},{-154291366,1062598550},{-549185496,922668301},{264092224,1040757801},{742770847,775379244},{-23057618,1073494224},{389505993,1000603111},{-432110916,982955574},{577229727,905387953},{-232042906,1048369016},{-615573145,879767700},{186813761,1057365652},{663193747,844449855},{-128167423,1066065014},{289554159,1033963197},{-526376678,935868098},{-698841306,815194659},{82274244,1070585098},{485706670,957606670},{-333683689,1020576650},{-737999227,779922204},{29644020,1073332537},{438134083,980285687},{-383359075,1002974238},{620959710,875974053},{-180322371,1058492015},{-571663505,908912724},{238471209,1046925492},{703830091,810891303},{-75703709,1071069770},{339939548,1018509994},{-479821763,960568883},{-657999815,848503239},{134706262,1065258526},{532109148,932620694},{-283204430,1035720404},{-752230014,-766205918},{9882456,-1073696345},{-401755603,-995747929},{420016001,-988184225},{-588296766,-898236282},{219160333,-1051137599},{604730690,-887255485},{-199775197,-1054993542},{-673506508,-836247862},{115075515,-1067557553},{-302220675,-1030332066},{514852501,-942257080},{688784992,-823709134},{-95405775,-1069494853},{-497421404,-951574195},{321134518,-1024594615},{-713727978,-802193167},{62554335,-1071918121},{-352412636,-1014261720},{467997975,-966384705},{-543513771,-926020671},{270473222,-1039117770},{647537829,-856514018},{-147768480,-1063525261},{728372812,-788919863},{-42813229,-1072887940},{-450130706,-974835294},{371022172,-1007603122},{-631662502,-868287963},{167319467,-1060625145},{560466703,-915859475},{-251300639,-1043920252},{747514502,-770807091},{-16470347,-1073615495},{-426071479,-985588453},{395638246,-998194311},{-610163404,-883528225},{193298118,-1056199480},{582774217,-901829094},{-225605866,-1049773069},{-693826210,-819467323},{88841682,-1070060119},{-327415267,-1022604883},{491573291,-954608403},{668362709,-840364678},{-121623758,-1066831367},{-520624390,-939080267},{295892987,-1032167062},{-733199822,-784435800},{36229307,-1073130440},{-377197724,-1005307605},{444140755,-977578893},{-566075760,-912403275},{244890534,-1045442552},{626322896,-872147426},{-173824191,-1059578527},{708792377,-806557418},{-69130323,-1071514117},{-473918791,-963494932},{346182609,-1016404991},{-652781111,-852524677},{141240030,-1064411930},{537821584,-929338177},{-276844037,-1037438616}};

static complex_t post1[64]ICONST_ATTR={{1073721611,6588355},{1073559912,19764075},{1073236539,32936819},{1072751541,46104602},{1072104991,59265442},{1071296985,72417357},{1070327646,85558366},{1069197119,98686490},{1067905576,111799753},{1066453209,124896178},{1064840239,137973795},{1063066908,151030634},{1061133483,164064728},{1059040255,177074114},{1056787539,190056834},{1054375675,203010932},{1051805026,215934457},{1049075979,228825463},{1046188946,241682009},{1043144359,254502159},{1039942680,267283981},{1036584388,280025551},{1033069991,292724951},{1029400017,305380267},{1025575020,317989594},{1021595574,330551034},{1017462280,343062693},{1013175760,355522688},{1008736660,367929143},{1004145647,380280189},{999403414,392573967},{994510674,404808624},{989468165,416982318},{984276645,429093217},{978936897,441139495},{973449725,453119340},{967815955,465030947},{962036435,476872521},{956112036,488642280},{950043650,500338452},{943832191,511959274},{937478594,523502998},{930983817,534967883},{924348836,546352205},{917574653,557654248},{910662286,568872310},{903612776,580004702},{896427186,591049747},{889106597,602005783},{881652112,612871159},{874064853,623644238},{866345963,634323399},{858496605,644907034},{850517961,655393547},{842411231,665781361},{834177638,676068911},{825818420,686254647},{817334837,696337035},{808728167,706314558},{799999705,716185713},{791150766,725949012},{782182683,735602987},{773096806,745146182},{763894503,754577161}};

static complex_t pre2[64]ICONST_ATTR={{1073721611,-6588355},{763894503,754577161},{994510674,404808624},{416982318,989468165},{1054375675,203010932},{602005783,889106597},{215934457,1051805026},{896427186,591049747},{1069197119,98686490},{686254647,825818420},{950043650,500338452},{317989594,1025575020},{111799753,1067905576},{834177638,676068911},{1029400017,305380267},{511959274,943832191},{1072751541,46104602},{725949012,791150766},{973449725,453119340},{367929143,1008736660},{1043144359,254502159},{557654248,917574653},{164064728,1061133483},{866345963,634323399},{59265442,1072104991},{799999705,716185713},{1013175760,355522688},{465030947,967815955},{1063066908,151030634},{644907034,858496605},{267283981,1039942680},{924348836,546352205},{1073559912,19764075},{745146182,773096806},{984276645,429093217},{392573967,999403414},{1049075979,228825463},{580004702,903612776},{190056834,1056787539},{881652112,612871159},{1066453209,124896178},{665781361,842411231},{937478594,523502998},{292724951,1033069991},{85558366,1070327646},{817334837,696337035},{1021595574,330551034},{488642280,956112036},{32936819,1073236539},{782182683,735602987},{1004145647,380280189},{441139495,978936897},{1059040255,177074114},{623644238,874064853},{241682009,1046188946},{910662286,568872310},{1071296985,72417357},{706314558,808728167},{962036435,476872521},{343062693,1017462280},{137973795,1064840239},{850517961,655393547},{1036584388,280025551},{534967883,930983817}};
static complex_t post2[32]ICONST_ATTR={{1073660973,13176463},{1073014239,39521454},{1071721163,65842639},{1069782521,92124162},{1067199482,118350193},{1063973603,144504935},{1060106825,170572632},{1055601479,196537583},{1050460278,222384146},{1044686318,248096754},{1038283079,273659918},{1031254417,299058239},{1023604566,324276418},{1015338134,349299266},{1006460100,374111709},{996975812,398698801},{986890983,423045731},{976211688,447137835},{964944359,470960600},{953095785,494499675},{940673100,517740882},{927683790,540670222},{914135677,563273882},{900036924,585538247},{885396022,607449906},{870221790,628995659},{854523369,650162530},{838310215,670937766},{821592095,691308855},{804379078,711263525},{786681534,730789756},{768510121,749875787}};
