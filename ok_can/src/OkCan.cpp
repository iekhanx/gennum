/*
 * ========================================================================
 *
 *       Filename:  OkCan.cpp
 *
 *    Description:  OK Cancel Button creation class 
 *
 *        Version:  1.0
 *        Created:  12/03/22 16:35:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  © Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>   /* X org server lib */
#include <X11/Xutil.h>  /* X org Server lib */
#include <X11/Xos.h>    /* X org Server lib */
#include <X11/Xatom.h>  /* X org Server lib */
#include <X11/xpm.h>
#include <stdint.h>

/* XPM */
static char * NewQuestion_xpm[] = {
"100 100 744 2",
"  	c #FCFCFC",
". 	c #F7F7F7",
"+ 	c #F7F7F6",
"@ 	c #F7F7F5",
"# 	c #F7F6F3",
"$ 	c #F7F6F0",
"% 	c #F7F4EB",
"& 	c #F6F3E5",
"* 	c #F6F2E1",
"= 	c #F6F3E4",
"- 	c #F6F4EA",
"; 	c #F6F5ED",
"> 	c #F6F0DA",
", 	c #F6EBC6",
"' 	c #F6E5AE",
") 	c #F6DF91",
"! 	c #F6DA78",
"~ 	c #F7D760",
"{ 	c #F7D455",
"] 	c #F6D249",
"^ 	c #F6D243",
"/ 	c #F6D242",
"( 	c #F6D248",
"_ 	c #F7D453",
": 	c #F7D65E",
"< 	c #F6D971",
"[ 	c #F6DE8D",
"} 	c #F6E4A9",
"| 	c #F6EAC2",
"1 	c #F6EFD7",
"2 	c #F7F6F4",
"3 	c #F6F1E1",
"4 	c #F6EAC5",
"5 	c #F6DF94",
"6 	c #F6D56B",
"7 	c #F6D03E",
"8 	c #F7CD0E",
"9 	c #F7CC00",
"0 	c #F7CC07",
"a 	c #F6CF35",
"b 	c #F6D465",
"c 	c #F6DD8C",
"d 	c #F6E8BF",
"e 	c #F6F0DE",
"f 	c #F7F6F2",
"g 	c #F6F3E6",
"h 	c #F6E8B8",
"i 	c #F6D142",
"j 	c #F7CD12",
"k 	c #F7CC03",
"l 	c #F7CC02",
"m 	c #F7CD0D",
"n 	c #F6D03A",
"o 	c #F6D86F",
"p 	c #F6E6AF",
"q 	c #F6F2DF",
"r 	c #F6F0D9",
"s 	c #F6E29A",
"t 	c #F6D44A",
"u 	c #F7CC08",
"v 	c #F6D23F",
"w 	c #F6DF8D",
"x 	c #F6EED2",
"y 	c #F7F6F1",
"z 	c #F7F6F5",
"A 	c #F7F0DB",
"B 	c #F6DE95",
"C 	c #F6D03C",
"D 	c #F7CF2E",
"E 	c #F6DB86",
"F 	c #F6EED3",
"G 	c #F6F1DE",
"H 	c #F6E095",
"I 	c #F7D13C",
"J 	c #F7CF30",
"K 	c #F6DD88",
"L 	c #F6EFD5",
"M 	c #F7F5EE",
"N 	c #F6E7AF",
"O 	c #F7D245",
"P 	c #F7CC06",
"Q 	c #F7D036",
"R 	c #F6E49E",
"S 	c #F7F3E8",
"T 	c #F7F0DC",
"U 	c #F6DA79",
"V 	c #F7CC09",
"W 	c #F6D769",
"X 	c #F6EDD1",
"Y 	c #F6E8BD",
"Z 	c #F6D24A",
"` 	c #F7CC01",
" .	c #F6D036",
"..	c #F7F5ED",
"+.	c #F7F4EC",
"@.	c #F6E096",
"#.	c #F7CE2A",
"$.	c #F7CD19",
"%.	c #F6DC83",
"&.	c #F7F2E3",
"*.	c #F7F4E9",
"=.	c #F6DB7D",
"-.	c #F7CC04",
";.	c #F6D76A",
">.	c #F6F2E2",
",.	c #F6F1DD",
"'.	c #F6D875",
").	c #F6D45D",
"!.	c #F6EFD3",
"~.	c #F6F0DB",
"{.	c #F6D868",
"].	c #F7D451",
"^.	c #F6EECE",
"/.	c #F6D760",
"(.	c #F6D44F",
"_.	c #F6F0D7",
":.	c #F7F3E7",
"<.	c #F6D876",
"[.	c #F6CC00",
"}.	c #F1C900",
"|.	c #EBC400",
"1.	c #E2BB01",
"2.	c #DAB500",
"3.	c #CDAC03",
"4.	c #C9AA03",
"5.	c #CEAB02",
"6.	c #D8B300",
"7.	c #E2BC00",
"8.	c #F6D461",
"9.	c #F6F1E0",
"0.	c #F6DD87",
"a.	c #D1AD02",
"b.	c #A48902",
"c.	c #7C6701",
"d.	c #514302",
"e.	c #2C2402",
"f.	c #1F1801",
"g.	c #181301",
"h.	c #161201",
"i.	c #181300",
"j.	c #1E1700",
"k.	c #2A2201",
"l.	c #4C3F02",
"m.	c #7A6401",
"n.	c #A28701",
"o.	c #CEAB01",
"p.	c #EBC300",
"q.	c #F6D86A",
"r.	c #F6E3A3",
"s.	c #F7CD1D",
"t.	c #EDC500",
"u.	c #B69802",
"v.	c #6E5B02",
"w.	c #302701",
"x.	c #090600",
"y.	c #000000",
"z.	c #2C2201",
"A.	c #6A5702",
"B.	c #B59602",
"C.	c #F7CC0B",
"D.	c #F6DE89",
"E.	c #F6ECCC",
"F.	c #F7CE1F",
"G.	c #F5CB00",
"H.	c #CDAA01",
"I.	c #625001",
"J.	c #090601",
"K.	c #655202",
"L.	c #CCAB02",
"M.	c #F7CD14",
"N.	c #F6E6B4",
"O.	c #F7F1DE",
"P.	c #F6D246",
"Q.	c #EDC501",
"R.	c #A18601",
"S.	c #000001",
"T.	c #221C01",
"U.	c #967D02",
"V.	c #E8C001",
"W.	c #F6CB00",
"X.	c #F6D037",
"Y.	c #F7EED2",
"Z.	c #F6DC84",
"`.	c #EAC301",
" +	c #8B7402",
".+	c #100B00",
"++	c #7A6302",
"@+	c #D8B101",
"#+	c #F3C900",
"$+	c #F6D869",
"%+	c #F7F4E8",
"&+	c #F7E9BC",
"*+	c #F7CE26",
"=+	c #EFC801",
"-+	c #897302",
";+	c #0A0700",
">+	c #080500",
",+	c #6F5A02",
"'+	c #CFA901",
")+	c #EBC200",
"!+	c #F6E4A1",
"~+	c #F7F3E6",
"{+	c #F7D55B",
"]+	c #AC8F01",
"^+	c #151100",
"/+	c #040301",
"(+	c #7D6503",
"_+	c #CBA501",
":+	c #DFB700",
"<+	c #F2C800",
"[+	c #F7D13F",
"}+	c #F6E4AA",
"|+	c #F7CD0F",
"1+	c #D8B401",
"2+	c #433602",
"3+	c #221A02",
"4+	c #A58502",
"5+	c #CBA500",
"6+	c #D6AF00",
"7+	c #E9C000",
"8+	c #F5CA00",
"9+	c #F6DE8E",
"0+	c #F6F3E7",
"a+	c #F6D13D",
"b+	c #F2C900",
"c+	c #8C7501",
"d+	c #020200",
"e+	c #5C4A02",
"f+	c #C19D01",
"g+	c #CCA700",
"h+	c #D3AD00",
"i+	c #E0B800",
"j+	c #EFC500",
"k+	c #F7CF31",
"l+	c #F6EED7",
"m+	c #F6E19D",
"n+	c #D6B301",
"o+	c #271F01",
"p+	c #161101",
"q+	c #9C7E02",
"r+	c #C9A300",
"s+	c #CEA800",
"t+	c #D3AC00",
"u+	c #DBB300",
"v+	c #EAC100",
"w+	c #F6DC88",
"x+	c #997F02",
"y+	c #655102",
"z+	c #C39D01",
"A+	c #D0AA00",
"B+	c #D6AE00",
"C+	c #DDB401",
"D+	c #E6BD00",
"E+	c #F0C600",
"F+	c #F7CF2F",
"G+	c #F6EFD4",
"H+	c #F6E5AC",
"I+	c #F7CC11",
"J+	c #ECC500",
"K+	c #5B4B01",
"L+	c #322801",
"M+	c #B29002",
"N+	c #CEA700",
"O+	c #D2AB00",
"P+	c #D7B000",
"Q+	c #DEB501",
"R+	c #E5BB00",
"S+	c #EEC400",
"T+	c #F6CA00",
"U+	c #F6DF8F",
"V+	c #F6D766",
"W+	c #D5B301",
"X+	c #1E1801",
"Y+	c #0A0702",
"Z+	c #503F02",
"`+	c #7B6402",
" @	c #907503",
".@	c #8C7202",
"+@	c #6E5902",
"@@	c #382C02",
"#@	c #9B7D01",
"$@	c #C8A201",
"%@	c #D0A900",
"&@	c #D5AD01",
"*@	c #D9B201",
"=@	c #DFB701",
"-@	c #E5BC00",
";@	c #EDC400",
">@	c #F6D13F",
",@	c #F6F2E0",
"'@	c #F6ECCD",
")@	c #F7CE27",
"!@	c #BE9D01",
"~@	c #312601",
"{@	c #907402",
"]@	c #BF9B01",
"^@	c #C8A300",
"/@	c #B89501",
"(@	c #151001",
"_@	c #816803",
":@	c #CAA500",
"<@	c #CEA900",
"[@	c #D3AC01",
"}@	c #DBB401",
"|@	c #E2B800",
"1@	c #F4CA00",
"2@	c #F7CC0A",
"3@	c #F6E7B6",
"4@	c #F6E19E",
"5@	c #F7CD00",
"6@	c #A68A03",
"7@	c #1D1601",
"8@	c #967902",
"9@	c #C7A101",
"0@	c #C9A400",
"a@	c #CDA600",
"b@	c #CDA701",
"c@	c #7C6603",
"d@	c #635002",
"e@	c #C8A301",
"f@	c #CDA700",
"g@	c #D1AB00",
"h@	c #D6AE01",
"i@	c #DAB201",
"j@	c #DFB601",
"k@	c #E4BB00",
"l@	c #E8C000",
"m@	c #EEC500",
"n@	c #F6DA7B",
"o@	c #F7F5F1",
"p@	c #F6D55F",
"q@	c #8E7802",
"r@	c #5C4903",
"s@	c #C09C01",
"t@	c #CCA600",
"u@	c #CFA900",
"v@	c #D4AC01",
"w@	c #C19D02",
"x@	c #281F01",
"y@	c #4E4003",
"z@	c #C9A301",
"A@	c #D8B100",
"B@	c #E6BC00",
"C@	c #F1C600",
"D@	c #F6D144",
"E@	c #F6F0DD",
"F@	c #F7CE17",
"G@	c #857002",
"H@	c #010100",
"I@	c #856B02",
"J@	c #CCA500",
"K@	c #D2AC00",
"L@	c #D2AB01",
"M@	c #362B01",
"N@	c #4B3B03",
"O@	c #CBA600",
"P@	c #D7AF00",
"Q@	c #DCB401",
"R@	c #E4BA00",
"S@	c #E8BF00",
"T@	c #EDC300",
"U@	c #F3C800",
"V@	c #F7CB00",
"W@	c #F6EAC8",
"X@	c #F6E5AF",
"Y@	c #F7CC05",
"Z@	c #9D8302",
"`@	c #554402",
" #	c #534202",
".#	c #9D7F02",
"+#	c #D6AF01",
"@#	c #DAB101",
"##	c #CEA802",
"$#	c #4F4003",
"%#	c #DEB601",
"&#	c #E7BE00",
"*#	c #F6DE93",
"=#	c #F7F7F4",
"-#	c #F6DB85",
";#	c #E2BA00",
">#	c #CCA601",
",#	c #C5A001",
"'#	c #CAA400",
")#	c #BD9B02",
"!#	c #1C1601",
"~#	c #DAB200",
"{#	c #E2B900",
"]#	c #F6F5EC",
"^#	c #F0C700",
"/#	c #DDB600",
"(#	c #CFA800",
"_#	c #D4AD01",
":#	c #D9B200",
"<#	c #E0B701",
"[#	c #937802",
"}#	c #030201",
"|#	c #836A03",
"1#	c #E1B800",
"2#	c #F6D03D",
"3#	c #F6F0DC",
"4#	c #F7CC0C",
"5#	c #DBB400",
"6#	c #463902",
"7#	c #0F0B01",
"8#	c #A08102",
"9#	c #F5C900",
"0#	c #F6CC07",
"a#	c #F6EBC8",
"b#	c #F6EBC1",
"c#	c #EAC000",
"d#	c #DCB400",
"e#	c #D8B001",
"f#	c #D9B100",
"g#	c #DBB301",
"h#	c #DDB501",
"i#	c #9B7E02",
"j#	c #090701",
"k#	c #3E3101",
"l#	c #B79502",
"m#	c #F0C500",
"n#	c #F1C800",
"o#	c #F6E6AE",
"p#	c #F6E5AA",
"q#	c #BB9802",
"r#	c #392E01",
"s#	c #755E03",
"t#	c #C59F01",
"u#	c #F6E093",
"v#	c #F6E094",
"w#	c #F2C700",
"x#	c #E9BF00",
"y#	c #574602",
"z#	c #2A2101",
"A#	c #A88902",
"B#	c #D1AA00",
"C#	c #F7CA00",
"D#	c #F6DA76",
"E#	c #F6DC81",
"F#	c #E3BB00",
"G#	c #715C02",
"H#	c #020201",
"I#	c #030200",
"J#	c #755F02",
"K#	c #DBB201",
"L#	c #F7D762",
"M#	c #F6D978",
"N#	c #F1C700",
"O#	c #E4BC01",
"P#	c #866E02",
"Q#	c #050400",
"R#	c #392E02",
"S#	c #B69302",
"T#	c #DCB301",
"U#	c #F6D557",
"V#	c #F6F5EE",
"W#	c #F6D76C",
"X#	c #F4C900",
"Y#	c #E9C201",
"Z#	c #8D7503",
"`#	c #161001",
" $	c #1D1701",
".$	c #997C02",
"+$	c #F6D34A",
"@$	c #F6F4EB",
"#$	c #F6D666",
"$$	c #F4CB00",
"%$	c #9C8303",
"&$	c #7E6502",
"*$	c #E1B801",
"=$	c #F6D245",
"-$	c #F6F2E3",
";$	c #F6D665",
">$	c #B19302",
",$	c #130E01",
"'$	c #080600",
")$	c #6D5803",
"!$	c #BE9A01",
"~$	c #ECC300",
"{$	c #F6D768",
"]$	c #C2A101",
"^$	c #564602",
"/$	c #BA9602",
"($	c #F6F2E4",
"_$	c #DEB800",
":$	c #564702",
"<$	c #E3BA00",
"[$	c #F7D34D",
"}$	c #927A03",
"|$	c #030301",
"1$	c #322702",
"2$	c #A58603",
"3$	c #D5AE01",
"4$	c #E5BD00",
"5$	c #EFC400",
"6$	c #F6D55A",
"7$	c #F6F5F0",
"8$	c #F6DD85",
"9$	c #D8B502",
"0$	c #312803",
"a$	c #181201",
"b$	c #937702",
"c$	c #C6A001",
"d$	c #F6D864",
"e$	c #F6E19A",
"f$	c #A28601",
"g$	c #6D5802",
"h$	c #C39E01",
"i$	c #E0B801",
"j$	c #F6DC80",
"k$	c #EEC700",
"l$	c #403303",
"m$	c #2F2403",
"n$	c #F6E198",
"o$	c #F6EDC9",
"p$	c #F7CB01",
"q$	c #D3AF01",
"r$	c #735D03",
"s$	c #C7A201",
"t$	c #E6BE00",
"u$	c #F6E8B6",
"v$	c #F6CE22",
"w$	c #B29502",
"x$	c #A78702",
"y$	c #D8B000",
"z$	c #F6CD1A",
"A$	c #F6EDCE",
"B$	c #F7F5EC",
"C$	c #F6D55D",
"D$	c #A28702",
"E$	c #493A02",
"F$	c #BD9A01",
"G$	c #CFAA00",
"H$	c #E3B900",
"I$	c #ECC200",
"J$	c #F6D14C",
"K$	c #F6DD8F",
"L$	c #9C8103",
"M$	c #5E4C02",
"N$	c #C49F02",
"O$	c #F7D774",
"P$	c #F7F5EF",
"Q$	c #F6E8BB",
"R$	c #F7CD08",
"S$	c #A08503",
"T$	c #6F5A03",
"U$	c #E9C100",
"V$	c #F6E2A0",
"W$	c #F7F2E5",
"X$	c #F7CF27",
"Y$	c #D5B202",
"Z$	c #9E8203",
"`$	c #927603",
" %	c #F7CD1A",
".%	c #F6ECD0",
"+%	c #F6D972",
"@%	c #F6D351",
"#%	c #F6E5AD",
"$%	c #C39F01",
"%%	c #A28401",
"&%	c #8B7002",
"*%	c #7F6803",
"=%	c #866C03",
"-%	c #9C7F01",
";%	c #B49302",
">%	c #C8A400",
",%	c #F4C800",
"'%	c #F6DE8B",
")%	c #F6F0D8",
"!%	c #F7D035",
"~%	c #E1BB01",
"{%	c #977E01",
"]%	c #4A3B01",
"^%	c #0E0A01",
"/%	c #040300",
"(%	c #2F2602",
"_%	c #6E5A03",
":%	c #B69502",
"<%	c #D5AE00",
"[%	c #D9B101",
"}%	c #F3C700",
"|%	c #F7F5F0",
"1%	c #F6DB7A",
"2%	c #5F4E02",
"3%	c #060400",
"4%	c #392D01",
"5%	c #A98902",
"6%	c #D7B001",
"7%	c #F6D552",
"8%	c #F6E9B8",
"9%	c #F7CD18",
"0%	c #E3BF01",
"a%	c #4D4002",
"b%	c #302501",
"c%	c #B39101",
"d%	c #F6E4A0",
"e%	c #F6D45C",
"f%	c #F3CB00",
"g%	c #947C02",
"h%	c #010101",
"i%	c #695502",
"j%	c #D4AD00",
"k%	c #E7BF00",
"l%	c #E4BD01",
"m%	c #2B2202",
"n%	c #B19001",
"o%	c #C9A401",
"p%	c #DEB600",
"q%	c #F6E1A1",
"r%	c #281F00",
"s%	c #9C7E03",
"t%	c #F6EAC1",
"u%	c #F7CE1A",
"v%	c #BDA003",
"w%	c #907403",
"x%	c #F7CD0C",
"y%	c #F6E3A4",
"z%	c #C1A203",
"A%	c #1F1900",
"B%	c #927704",
"C%	c #E1B901",
"D%	c #F6D457",
"E%	c #F6EDCC",
"F%	c #F7D039",
"G%	c #D7B300",
"H%	c #322901",
"I%	c #100C01",
"J%	c #F7CD15",
"K%	c #F5E2A1",
"L%	c #6D5A03",
"M%	c #493B02",
"N%	c #BC9902",
"O%	c #F6DD8A",
"P%	c #F6F4ED",
"Q%	c #F6D76F",
"R%	c #C4A301",
"S%	c #1D1602",
"T%	c #917503",
"U%	c #CBA400",
"V%	c #F6D45B",
"W%	c #F5D241",
"X%	c #F3CA00",
"Y%	c #A58902",
"Z%	c #211A01",
"`%	c #0B0800",
" &	c #6E5903",
".&	c #C19C01",
"+&	c #F6CF30",
"@&	c #F6E9BC",
"#&	c #F7CF2D",
"$&	c #AD9001",
"%&	c #352B01",
"&&	c #766002",
"*&	c #BC9801",
"=&	c #F6E4A5",
"-&	c #F6E3A7",
";&	c #F7CC19",
">&	c #DFBA01",
",&	c #A08402",
"'&	c #584803",
")&	c #362A01",
"!&	c #2F2500",
"~&	c #322701",
"{&	c #786102",
"]&	c #AA8B03",
"^&	c #C6A101",
"/&	c #F6DD8D",
"(&	c #CAA501",
"_&	c #B89502",
":&	c #BA9702",
"<&	c #F6DA81",
"[&	c #F5DE85",
"}&	c #F6CC09",
"|&	c #F5D96F",
"1&	c #F7F3E5",
"2&	c #F6DE87",
"3&	c #F5D76B",
"4&	c #F6DF97",
"5&	c #F7CD1B",
"6&	c #DEB500",
"7&	c #D7AF01",
"8&	c #F7CC12",
"9&	c #F6DA80",
"0&	c #F7F4E7",
"a&	c #F6E3A5",
"b&	c #F6CF2E",
"c&	c #F7CE22",
"d&	c #F6E9BE",
"e&	c #F7CF2B",
"f&	c #F6D76D",
"g&	c #F6D45A",
"h&	c #F6F4E8",
"i&	c #F6E3A1",
"j&	c #F6DF92",
"k&	c #F7CD16",
"l&	c #F6EBC9",
"m&	c #F6EAC3",
"n&	c #F6D561",
"o&	c #F6D24F",
"p&	c #F6E7B3",
"q&	c #F6D661",
"r&	c #F7CD1C",
"s&	c #F7F3E3",
"t&	c #F7EAC2",
"u&	c #F6D035",
"v&	c #F7CD06",
"w&	c #F6CE24",
"x&	c #F6D979",
"y&	c #F6E8B9",
"z&	c #F7F3E4",
"A&	c #F6F1DF",
"B&	c #F6E5B1",
"C&	c #F6D97E",
"D&	c #F6CE23",
"E&	c #F6D772",
"F&	c #F6E3AA",
"G&	c #F7F2E0",
"H&	c #F7CC0E",
"I&	c #F7CC0D",
"J&	c #F7CC14",
"K&	c #F6D02F",
"L&	c #F6E7B0",
"M&	c #F6F1DC",
"N&	c #F7F1DD",
"O&	c #F7EECD",
"P&	c #F6E8B7",
"Q&	c #F5E2A0",
"R&	c #F5DB82",
"S&	c #F6D975",
"T&	c #F6D96F",
"U&	c #F6D96E",
"V&	c #F6D974",
"W&	c #F5DB80",
"X&	c #F6DD8B",
"Y&	c #F6E29D",
"Z&	c #F6E8B5",
"`&	c #F7EDCA",
" *	c #F7F1DA",
".*	c #F7F4EA",
"+*	c #F8F9FA",
"@*	c #F8F8F9",
"#*	c #F7F7F8",
"$*	c #FEFEFE",
"%*	c #FDFDFD",
"&*	c #FFFFFF",
"                                                                                                                                                                                                        ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . + @ # $ % & * * * = - $ # @ + . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . @ ; > , ' ) ! ~ { ] ^ / / ( _ : < [ } | 1 - 2 + . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 2 3 4 5 6 7 8 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 0 a b c d e f . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . g h ! i j k 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 l m n o p q + . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . # r s t u 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 k v w x y . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . z A B C 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 D E F f . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . + G H I k 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 l J K L . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . M N O P 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 k Q R S . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . T U j 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 V W X + . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . y Y Z ` 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 `  .' ... . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . +.@.#.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 $.%.&.. . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . *.=.u 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 -.;.>.. . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . ,.'.l 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 ` ).!.+ . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . ~.{.-.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 ].^.+ . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . = /.k 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 l (._.. . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . :.<.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 [.}.|.1.2.3.4.5.6.7.|.}.[.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 8.9.. . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . % 0.u 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 [.|.a.b.c.d.e.f.g.h.i.j.k.l.m.n.o.p.[.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 q.&.. . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . 2 r.s.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 [.t.u.v.w.x.y.y.y.y.y.y.y.y.y.y.y.x.z.A.B.|.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 C.D.M . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . E.F.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 G.H.I.x.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.J.K.L.G.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 M.N.+ . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . O.P.` 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 Q.R.k.S.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.T.U.V.W.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 X.Y.. . . . . . . . . . . . . . ",
". . . . . . . . . . . . M Z.` 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 `. +i.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y..+++@+#+9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 $+%+. . . . . . . . . . . . . ",
". . . . . . . . . . . . &+*+9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 =+-+;+y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.>+,+'+)+9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 0 !+. . . . . . . . . . . . . ",
". . . . . . . . . . . ~+{+9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 [.]+^+y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y./+(+_+:+<+9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 [+1 . . . . . . . . . . . . ",
". . . . . . . . . . + }+|+9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 1+2+y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.3+4+5+6+7+8+9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 P 9+f . . . . . . . . . . . ",
". . . . . . . . . . 0+a+9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 b+c+d+y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.e+f+g+h+i+j+9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 k+l+. . . . . . . . . . . ",
". . . . . . . . . z m+l 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 n+o+y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.p+q+r+s+t+u+v+8+9 9 9 9 9 9 9 9 9 9 9 9 9 9 l w+f . . . . . . . . . . ",
". . . . . . . . . q ( 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 [.x+y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y+z+5+A+B+C+D+E+W.9 9 9 9 9 9 9 9 9 9 9 9 9 F+G+. . . . . . . . . . ",
". . . . . . . . + H+I+9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 J+K+y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.L+M+r+N+O+P+Q+R+S+T+9 9 9 9 9 9 9 9 9 9 9 9 9 U++ . . . . . . . . . ",
". . . . . . . . % V+9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 W+X+y.y.y.y.y.y.y.y.y.y.y.y.Y+Z+`+ @.@+@@@d+y.y.y.y.y.y.y.y.y.y.y.y.y.>+#@$@5+%@&@*@=@-@;@8+9 9 9 9 9 9 9 9 9 9 9 9 >@,@. . . . . . . . . ",
". . . . . . . . '@)@9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 !@S.y.y.y.y.y.y.y.y.y.y.y.~@{@]@$@$@r+^@/@++(@y.y.y.y.y.y.y.y.y.y.y.y.y._@$@:@<@[@6+}@|@D+S+1@9 9 9 9 9 9 9 9 9 9 9 2@3@. . . . . . . . . ",
". . . . . . . + 4@P 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 5@6@y.y.y.y.y.y.y.y.y.y.y.7@8@9@$@0@5+a@s+s+b@c@/+y.y.y.y.y.y.y.y.y.y.y.y.d@e@0@f@g@h@i@j@k@l@m@8+9 9 9 9 9 9 9 9 9 9 ` n@# . . . . . . . . ",
". . . . . . . o@p@9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 5@q@y.y.y.y.y.y.y.y.y.y.y.r@s@$@0@t@s+u@g@[@v@w@x@y.y.y.y.y.y.y.y.y.y.y.y.y@z@r+a@A+&@A@C+|@B@v+C@T+9 9 9 9 9 9 9 9 9 9 D@>.. . . . . . . . ",
". . . . . . . E@F@9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 5@G@y.y.y.y.y.y.y.y.y.y.H@I@$@e@J@s+A+K@&@h@P+L@M@y.y.y.y.y.y.y.y.y.y.y.y.N@e@r+O@u@[@P@Q@=@R@S@T@U@V@9 9 9 9 9 9 9 9 9 8 W@+ . . . . . . . ",
". . . . . . . X@Y@9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 5@Z@`@ # # # # # # # # # #.#e@0@a@u@O+&@+#A@@###w.y.y.y.y.y.y.y.y.y.y.y.y.$#z@r+O@u@[@P@i@%#R@&#)+C@1@9 9 9 9 9 9 9 9 9 l *#=#. . . . . . . ",
". . . . . . # -#9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 #+;#>#,#,#,#,#,#,#,#,#,#9@r+'#f@A+v@h@A@i@C+)#!#y.y.y.y.y.y.y.y.y.y.y.y.K.$@r+O@u@[@P@~#%#{#B@v+S+<+V@9 9 9 9 9 9 9 9 9 6 ]#. . . . . . . ",
". . . . . . %+( 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 ^#/#s+t@t@t@t@t@t@t@t@t@t@(#A+_#P@:#Q@<#[#}#y.y.y.y.y.y.y.y.y.y.y.y.|#$@r+t@u@[@P@:#%#1#R+7+T@C@T+9 9 9 9 9 9 9 9 9 2#3#. . . . . . . ",
". . . . . . _.4#9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 [.;@5#K@g@g@g@g@g@g@g@g@g@O+&@A@i@%#+#6#y.y.y.y.y.y.y.y.y.y.y.y.7#8#$@0@t@u@[@P@A@%#1#R+&#)+E+9#9 9 9 9 9 9 9 9 9 0#a#. . . . . . . ",
". . . . . . b#V@9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 G.c#d#e#e#e#e#e#e#e#e#e#e#f#g#h#i#j#y.y.y.y.y.y.y.y.y.y.y.y.k#l#$@'#t@u@[@P@:#%#1#k@&#)+m#n#W.9 9 9 9 9 9 9 9 V@o#. . . . . . . ",
". . . . . . p#9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 <+&#=@Q+Q+Q+Q+Q+Q+Q+Q+Q+Q+q#r#y.y.y.y.y.y.y.y.y.y.y.y.H@s#t#$@5+s+A+&@P@~#%#1#R@&#)+m#n#V@9 9 9 9 9 9 9 9 9 u#. . . . . . . ",
". . . . . . v#9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 [.w#x#R@R@R@R@R@R@R@k@K@y#H@y.y.y.y.y.y.y.y.y.y.y.y.z#A#$@0@t@u@B#&@P@~#h#1#R@&#)+j+w#C#9 9 9 9 9 9 9 9 9 D#@ . . . . . . ",
". . . . . 2 E#9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 W.C@)+v+v+v+v+v+F#G#H#y.y.y.y.y.y.y.y.y.y.y.y.I#J#,#$@'#f@u@K@&@A@K#%#1#k@&#)+E+n#W.9 9 9 9 9 9 9 9 9 L#2 . . . . . . ",
". . . . . y M#9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 G.N#m#j+j+O#P#Q#y.y.y.y.y.y.y.y.y.y.y.y.y.R#S#$@r+J@s+A+_#h@A@T#%#{#k@&#)+E+n#W.9 9 9 9 9 9 9 9 9 U#V#. . . . . . ",
". . . . . ..W#9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 V@X#Y#Z#`#y.y.y.y.y.y.y.y.y.y.y.y.y. $.$$@e@0@f@u@O+&@P@i@h#j@R@-@S@)+m#n#W.9 9 9 9 9 9 9 9 9 +$0+. . . . . . ",
". . . . . @$#$9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 $$%$(@y.y.y.y.y.y.y.y.y.y.y.y.y.>+&$,#e@0@5+u@A+v@h@A@g#%#*$R@D+7+)+E+}.W.9 9 9 9 9 9 9 9 9 =$-$. . . . . . ",
". . . . . @$;$9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 1@>$,$y.y.y.y.y.y.y.y.y.y.y.y.y.'$)$!$$@0@J@s+u@O+&@P+i@h#=@R@R+&#)+~$C@X#V@9 9 9 9 9 9 9 9 9 ^ -$. . . . . . ",
". . . . . +.{$9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 W.]$z#y.y.y.y.y.y.y.y.y.y.y.y.y.H@^$/$$@^@5+f@u@O+&@+#f#T#%#1#R@-@7+)+j+C@9#9 9 9 9 9 9 9 9 9 9 =$($. . . . . . ",
". . . . . M o 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 _$:$y.y.y.y.y.y.y.y.y.y.y.y.y.y.@@M+$@r+'#f@u@A+_#+#A@K#Q+=@<$k@&#v+T@C@<+T+9 9 9 9 9 9 9 9 9 9 [$*.. . . . . . ",
". . . . . f n@9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 1@}$|$y.y.y.y.y.y.y.y.y.y.y.y.y.1$2$$@z@0@J@s+A+_#3$A@~#h#j@{#R@4$S@)+5$C@#+W.9 9 9 9 9 9 9 9 9 9 6$7$. . . . . . ",
". . . . . @ 8$9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9$0$y.y.y.y.y.y.y.y.y.y.y.y.y.a$b$c$e@'#t@s+A+t+&@P+f#Q@%#1#R@-@&#v+T@C@N#8+9 9 9 9 9 9 9 9 9 9 9 d$=#. . . . . . ",
". . . . . . e$9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 G.f$/+y.y.y.y.y.y.y.y.y.y.y.y.I#g$h$$@0@J@s+A+K@&@P+f#T#%#i$R@-@&#v+)+j+C@b+W.9 9 9 9 9 9 9 9 9 9 9 j$. . . . . . . ",
". . . . . . o#9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 k$l$y.y.y.y.y.y.y.y.y.y.y.y.y.m$M+$@r+5+f@u@K@&@P+f#T#h#i$R@R@&#v+)+S+C@w#C#9 9 9 9 9 9 9 9 9 9 9 9 n$. . . . . . . ",
". . . . . . o$p$9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 q$d+y.y.y.y.y.y.y.y.y.y.y.y.y.r$s$e@'#f@u@g@_#h@A@K#h#j@{#k@t$7+)+T@C@<+C#V@9 9 9 9 9 9 9 9 9 9 9 p$u$. . . . . . . ",
". . . . . . ,.v$9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 5@w$H@y.y.y.y.y.y.y.y.y.y.y.y.h.x$$@r+J@(#A+_#&@y$i@h#j@{#R@D+S@)+T@C@n#X#V@9 9 9 9 9 9 9 9 9 9 9 9 z$A$. . . . . . . ",
". . . . . . B$C$9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 D$H@y.y.y.y.y.y.y.y.y.y.y.y.E$F$$@'#f@G$t+&@P+i@C+%#H$R@B@&#v+I$E+C@X#W.9 9 9 9 9 9 9 9 9 9 9 9 9 J$* . . . . . . . ",
". . . . . . 2 K$9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 W.L$y.y.y.y.y.y.y.y.y.y.y.y.y.M$N$0@:@s+A+v@B+f#K#h#<#R@-@&#v+)+j+C@9#V@9 9 9 9 9 9 9 9 9 9 9 9 9 9 O$P$. . . . . . . ",
". . . . . . . Q$R$9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 S$'$'$'$'$'$'$'$'$'$'$'$'$'$T$9@r+t@u@g@&@P+i@C+=@R@R@&#U$)+j+N#9#C#9 9 9 9 9 9 9 9 9 9 9 9 9 9 -.V$@ . . . . . . . ",
". . . . . . . W$X$9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 Y$Z$`$`$`$`$`$`$`$`$`$`$`$`$2$$@0@t@u@O+h@A@K#%#|@R@D+S@)+T@C@b+C#V@9 9 9 9 9 9 9 9 9 9 9 9 9 9  %.%. . . . . . . . ",
". . . . . . . f +%9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 #+i+>#r+0@'#5+5+'#0@0@r+r+$@e@r+t@u@v@h@f#h#=@R@R+&#v+T@C@C@9#9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 @%0+. . . . . . . . ",
". . . . . . . . #%|+9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 W.v+$%%%&%*%=%-%;%>%f@f@f@f@f@s+A+_#P@f#h#<#R@-@S@)+j+C@,%V@9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 l '%@ . . . . . . . . ",
". . . . . . . . )%!%9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 ~%{%]%^%y.y.y./%(%_%:%&@<%<%<%<%<%h@+#[%h#{#R@D+v+~$C@}%T+9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 M.| . . . . . . . . . ",
". . . . . . . . |%1%9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 1+2%3%y.y.y.y.y.y.y.y.4%5%6%:#f#f#f#f#f#K#h#{#k@&#)+S+C@9#V@9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 7%*.. . . . . . . . . ",
". . . . . . . . . 8%9%9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 0%a%H@y.y.y.y.y.y.y.y.y.y.b%c%e#Q+j@j@j@j@j@<#{#k@&#)+5$n#8+V@9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 ` d%. . . . . . . . . . ",
". . . . . . . . . %+e%9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 f%g%h%y.y.y.y.y.y.y.y.y.y.y.y.i%,#j%1#4$-@-@-@-@-@4$k%)+j+}.8+9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 ( ,@. . . . . . . . . . ",
". . . . . . . . . + N.Y@9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 l%a%y.y.y.y.y.y.y.y.y.y.y.y.y.m%n%o%A+p%l@)+)+I$I$I$I$T@j+X#W.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 k q%@ . . . . . . . . . . ",
". . . . . . . . . . P$6$9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 H.r%y.y.y.y.y.y.y.y.y.y.y.y.y.H@s%$@5+B#i@x#E+N#w#w#w#w#w#X#V@9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 O 9.. . . . . . . . . . . ",
". . . . . . . . . . . t%u%9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 5@v% $y.y.y.y.y.y.y.y.y.y.y.y.y.y.w%$@0@s+O+A@k@N#W.9 9 9 9 W.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 x%y%+ . . . . . . . . . . . ",
". . . . . . . . . . . M D#l 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 5@z%A%y.y.y.y.y.y.y.y.y.y.y.y.y.y.B%$@'#s+g@h@*@C%T@G.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 D%($. . . . . . . . . . . . ",
". . . . . . . . . . . . E%F%9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 G%H%y.y.y.y.y.y.y.y.y.y.y.y.y.I%4+$@'#s+A+&@y$h#<$U$<+W.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 J%h + . . . . . . . . . . . . ",
". . . . . . . . . . . . # K%-.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 J+L%y.y.y.y.y.y.y.y.y.y.y.y.y.M%N%$@'#s+A+&@P+g#<#k@7+C@V@9 9 9 9 9 9 9 9 9 9 9 9 9 9 ` O%y . . . . . . . . . . . . . ",
". . . . . . . . . . . . . P%Q%l 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 R%S%y.y.y.y.y.y.y.y.y.y.y.^%T%$@r+U%s+B#&@P+K#%#H$D+v+w#V@9 9 9 9 9 9 9 9 9 9 9 9 ` V%-$. . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . > W%9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 X%Y%Z%y.y.y.y.y.y.y.y.y.`% &.&e@0@J@u@g@&@P+K#%#{#D+v+S+X#9 9 9 9 9 9 9 9 9 9 9 9 +&, . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . + @&#&9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 N#$&%&H@y.y.y.y.y.y.p+&&*&$@z@:@N+G$[@&@P+K#%#{#-@7+~$C@W.9 9 9 9 9 9 9 9 9 9 M.=&# . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . # -&;&9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 [.>&,&'&)&!&~&2+{&]&^&$@0@:@f@u@B#_#h@f#Q@j@H$-@&#~$C@9#9 9 9 9 9 9 9 9 9 Y@/&|%. . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . y B 2@9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 G.D+(&_&:&h$^&$@z@0@J@a@u@B#t+h@y$i@h#=@R@D+7+~$C@,%V@9 9 9 9 9 9 9 P <&... . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . ..[&}&9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 U@;#%@5+'#'#f@f@u@u@g@v@h@y$f#Q@%#{#k@D+v+~$C@b+V@9 9 9 9 9 9 -.|&1&. . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . +.2&k 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 N#i+O+A+A+A+t+v@&@3$A@f#C+%#=@k@-@&#v+~$C@#+V@9 9 9 9 9 ` 3&-$. . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . ..4&5&9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 W.S+6&6%7&7&P+y$:#i@C+%#<#R@R+D+l@)+m#C@8+9 9 9 9 9 8&9&0&. . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . P$a&b&9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 1@v+*$h#h#h#%#%#i$|@R@R+&#S@v+;@C@<+T+9 9 9 9 c&5 % . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . # d&=$` 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 X#v+k@R@<$<$R@k@B@&#7+)+S+C@n#9#9 9 9 9 e&o#P$. . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . E@f&m 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 #+I$7+&#S@7+7+)+I$S+C@N#9#V@9 9 V g&X + . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . h&i&I -.9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 W.U@S+S+S+S+S+E+w#,%X#W.9 ` D j&* . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . 2 F =.k&9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 W.T+X#,%,%X#T+V@V@9 8 $+l&y . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . f m&n&9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 o&3@|%. . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . *.p&q&r&l 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 ` 9%{ =&s&+ . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . *.t&Z.u&R$9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 v&w&x&y&z&+ . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . f A&B&C&+&` 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 D&E&F&E@|%. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . y G&8%'%q&X.k&H&P l ` 9 9 9 9 9 9 ` Y@I&J&K&6$8$L&M&P$+ . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . + +.N&O&P&Q&[ R&S&T&U&U&V&W&X&Y&Z&`& *.*@ . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . + # 7$7$7$f + . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
"+*+*+*+*+*+*+*+*+*+*+*+*@*#*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ",
"$*$*$*$*$*$*$*$*$*$*$*$*$*$*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*%*",
"&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*",
"&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*"};
///////////////////////////////////////////////////////////////////////////////
int showImage(Display *dpy, Window win, char *xpm[], int width, int height) 
{
    XImage *img;

    if (XpmCreateImageFromData (dpy, xpm, &img, NULL, NULL)) {
        fprintf(stderr, "Can't read image.\n");
        return 0;
    } else {
        int x = (width - img->width)/2;
        int y = (height - img->height)/2;

        GC gc = XCreateGC(dpy, win, 0, NULL);

        XPutImage(dpy, win, gc, img, 0, 0, x, y, img->width, img->height);
        XFreeGC(dpy, gc);
        return 1;
    }
}
///////////////////////////////////////////////////////////////////////////////

int main (int argc, char **argv)
{   
    Display *dpy;   /* X server connection */
    int      scrn;  /* Number of screen    */
    
    Window   win;        /* Window handle                */
    Window   childwin1;  /* Child window button ok      */
    Window   childwin2;  /* Child window buttton cancel */
    XEvent   ev;         /* Event handler for window     */
    /* Geometry variable wiindow */
    int       x, y;
    uint32_t  width, height;
    Window    root_win;
    Colormap  colormap;
    XColor    button_color;
    XColor    lightgray_color, darkgray_color;
    XGCValues gcv_lightgray, gcv_darkgray;
    GC        gc_lightgray, gc_darkgray, gc;
    unsigned int border_width, depth;
    int8_t    done =0;

    /* Text related declaration vars */
    XFontStruct  *font;
    XTextItem    ti[1];
    const char * fontname = "-*-helvetica-*-r-*-*-28-*-*-*-*-*-*-*";

    dpy = XOpenDisplay (NULL);    /* call X server connection. */
    if (dpy == NULL) {
        fprintf (stderr, "Cannot open display\n");
        exit (-1);   /* Exit if we cannot get x server connection */
    }

    /* Now get screen number or an id */
    scrn = DefaultScreen (dpy);

    /* Create window with our choice */
    win = XCreateSimpleWindow (dpy,
                         RootWindow (dpy, scrn),
                         700, 400, 400, 200,  /* X top X Bob Y top Y bottom */
                         1,                   /* Depth of window            */
                         BlackPixel (dpy, scrn),
                         WhitePixel (dpy, scrn) );

    /* Event management loop */
    XSelectInput (dpy, win, ExposureMask | KeyPressMask); /* Event mangement */
    gc = XCreateGC (dpy, win, 0, NULL);


    /* Map window for display */
    XMapWindow (dpy, win);

    /* A Child window color change with custom colors */
    colormap = DefaultColormap (dpy, scrn);
    XParseColor (dpy, colormap, "rgb:cc/cc/cc", &button_color);
    XAllocColor (dpy, colormap, &button_color);

    XParseColor (dpy, colormap, "rgb:ee/ee/ee", &lightgray_color);
    XAllocColor (dpy, colormap, &lightgray_color);
    gcv_lightgray.foreground = lightgray_color.pixel;
    gcv_lightgray.background = button_color.pixel;
    gc_lightgray = XCreateGC (dpy, RootWindow (dpy, scrn),
                              GCForeground | GCBackground,
                              &gcv_lightgray);


    XParseColor (dpy, colormap, "rgb:88/88/88", &lightgray_color);
    XAllocColor (dpy, colormap, &darkgray_color);
    gcv_darkgray.foreground = darkgray_color.pixel;
    gcv_darkgray.background = button_color.pixel;
    gc_darkgray = XCreateGC (dpy, RootWindow (dpy, scrn),
                              GCForeground | GCBackground,
                              &gcv_darkgray);

    XGetGeometry (dpy, win, &root_win, &x, &y, &width, &height,
                                    &border_width, &depth);
    printf ("W:%d  H:%d\n", width, height);

    /* Create CHILD window with our choice */
    childwin1 = XCreateSimpleWindow (dpy,
                         win,
                         60, 100, 100, 60,  /* X top X tob Y top Y bottom */
                         1,                   /* Depth of window          */
                         BlackPixel (dpy, scrn),
                         button_color.pixel);

    childwin2 = XCreateSimpleWindow (dpy,
                         win,
                         230, 100, 100, 60,  /* X top X tob Y top Y bottom */
                         1,                   /* Depth of window          */
                         BlackPixel (dpy, scrn),
                         button_color.pixel);

    Atom wmDeleteMsg = XInternAtom (dpy, "WM_DELETE_WINDOW", False);
    XSetWMProtocols (dpy, win, &wmDeleteMsg, 1);

    XSelectInput (dpy, childwin1, 
                  ExposureMask    | 
                  KeyPressMask    |
                  ButtonPressMask |
                  ButtonReleaseMask);

     XSelectInput (dpy, childwin2, 
                  ExposureMask    | 
                  KeyPressMask    |
                  ButtonPressMask |
                  ButtonReleaseMask);                  
               
    XMapWindow (dpy, childwin1);
    XMapWindow (dpy, childwin2);

    /* Button window coordnate require XGeometry location */
    XGetGeometry (dpy, childwin1, &root_win, &x, &y, &width, &height,
                  &border_width, &depth);

    XGetGeometry (dpy, childwin2, &root_win, &x, &y, &width, &height,
                  &border_width, &depth);

    while (done == 0) {
        XNextEvent (dpy, &ev);
        switch (ev.type) {
            case Expose:
             { // stick our QuestionMark sign on the screen
             if (ev.xbutton.window == win) {
             font = XLoadQueryFont (dpy, fontname);

              XGetGeometry (dpy, win, &root_win, &x, &y, &width, &height,
                                    &border_width, &depth);
            if (showImage(dpy, win, NewQuestion_xpm, width, height)) {
                XFlush(dpy);
             }

              printf ("W:->%d  H:->%d\n", width, height);
              height=height-140;
              ti[0].chars  = "Are you sure to exit?";
              ti[0].nchars = 21;
              ti[0].delta  = 0;
              ti[0].font   = font->fid;
              XDrawText (dpy, win, gc,
                        ((width-XTextWidth(font, ti[0].chars, ti[0].nchars))/2),
                        (height-(font->ascent+font->descent)/2) +
                        font->ascent, ti, 1);
             printf ("W:(%d)  H:(%d)\n", width, height);

             XDrawLine(dpy,childwin1,gc_lightgray,0,0,width-1,0);
             XDrawLine(dpy,childwin1,gc_lightgray,0,0,0,height-1);
             XDrawLine(dpy,childwin1,gc_lightgray,width-1,0,width-1,height-1);
             XDrawLine(dpy,childwin1,gc_lightgray,0,height-1,width-1,height-1);

             XDrawLine(dpy,childwin2,gc_lightgray,0,0,width-1,0);
             XDrawLine(dpy,childwin2,gc_lightgray,0,0,0,height-1);
             XDrawLine(dpy,childwin2,gc_lightgray,width-1,0,width-1,height-1);
             XDrawLine(dpy,childwin2,gc_lightgray,0,height-1,width-1,height-1);

            XGetGeometry (dpy, childwin1, &root_win, &x, &y, &width, &height,
                                    &border_width, &depth);
            printf ("C1W:->%d  C1H:->%d\n", width, height);
             
            
              ti[0].chars  = "YES";
              ti[0].nchars = 3;
              ti[0].delta  = 0;
              ti[0].font   = font->fid;
              XDrawText (dpy, childwin1, DefaultGC(dpy,scrn),
                        ((width-XTextWidth(font, ti[0].chars, ti[0].nchars))/2),
                        ((height-(font->ascent+font->descent))/2) +
                        font->ascent, ti, 1);

            XGetGeometry (dpy, childwin2, &root_win, &x, &y, &width, &height,
                                    &border_width, &depth);
            printf ("C2W:->%d  C2H:->%d\n", width, height);

              ti[0].chars = "  NO";
              ti[0].nchars= 4;
              ti[0].delta = 0;
              ti[0].font = font->fid;
              XDrawText (dpy,childwin2,DefaultGC (dpy,scrn),
                        ((width=XTextWidth(font, ti[0].chars, ti[0].nchars))/2),
                        ((height-(font->ascent+font->descent))/2) +
                        font->ascent, ti, 1);  

              XUnloadFont (dpy, font->fid);
             }
              break;
             }
         case ButtonPress:
          {
            if(ev.xbutton.window == childwin1) {
                if (ev.xbutton.button == 1) {
            XGetGeometry (dpy, childwin1, &root_win, &x, &y, &width, &height,
                                    &border_width, &depth);
            XDrawLine(dpy,childwin1,gc_darkgray,0,0,width-1,0);
            XDrawLine(dpy,childwin1,gc_darkgray,0,0,0,height-1);
            XDrawLine(dpy,childwin1,gc_lightgray,width-1,0,width-1,height-1);
            XDrawLine(dpy,childwin1,gc_lightgray,0,height-1,width-1,height-1);
                printf ("Button OK smooched\n");
                }
            }
            if (ev.xbutton.window == childwin2) {
                if (ev.xbutton.button == 1) {
            XGetGeometry (dpy, childwin2, &root_win, &x, &y, &width, &height,
                                    &border_width, &depth);
            XDrawLine(dpy,childwin2,gc_darkgray,0,0,width-1,0);
            XDrawLine(dpy,childwin2,gc_darkgray,0,0,0,height-1);
            XDrawLine(dpy,childwin2,gc_lightgray,width-1,0,width-1,height-1);
            XDrawLine(dpy,childwin2,gc_lightgray,0,height-1,width-1,height-1);
                printf ("Button Cancel smooched\n");
                }
            }
            break;
          }
         case ButtonRelease:
          {
            if (ev.xbutton.window == childwin1) {
            XGetGeometry (dpy, childwin1, &root_win, &x, &y, &width, &height,
                                    &border_width, &depth);
            XDrawLine(dpy,childwin1,gc_lightgray,0,0,width-1,0);
            XDrawLine(dpy,childwin1,gc_lightgray,0,0,0,height-1);
            XDrawLine(dpy,childwin1,gc_lightgray,width-1,0,width-1,height-1);
            XDrawLine(dpy,childwin1,gc_lightgray,0,height-1,width-1,height-1);
            printf ("Ok Button Release\n"); done = 1;
          }
            if (ev.xbutton.window == childwin2) {
            XGetGeometry (dpy, childwin2, &root_win, &x, &y, &width, &height,
                                    &border_width, &depth);
            XDrawLine(dpy,childwin2,gc_lightgray,0,0,width-1,0);
            XDrawLine(dpy,childwin2,gc_lightgray,0,0,0,height-1);
            XDrawLine(dpy,childwin2,gc_lightgray,width-1,0,width-1,height-1);
            XDrawLine(dpy,childwin2,gc_lightgray,0,height-1,width-1,height-1);
            printf ("Cancel Button Release\n");
            done = 1;
          }
            break;
        }
       case ClientMessage:
          {
            if(ev.xclient.data.l[0] == wmDeleteMsg) {
                printf ("Shutting down!\n"); done = 1;
            }
          }
       }
    }

    printf ("Memory flushed out\n");
    XDestroyWindow (dpy, win);
    XCloseDisplay (dpy);

    return EXIT_SUCCESS;  // int main() end 
}
/*-------------------------- Eof Prog ----------------------------*/
