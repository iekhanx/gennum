/*
* ========================================================================
*
*       Filename:  adf_colors.h
*
*    Description: Sysinfo implementation file 
*
:*        Version:  1.4.1
*        Created:  26/11/21 16:01:04
*
*       Revision:  1/ Initial file creation for ANSI color code        08/13
*                  2/ New color codes added for 256 ANSI color code    03/16
*                  3/ New X11 Org color codes added for X11 Library    07/21
*
*       Compiler:  none
*
*         Author:  Imran Khan (C), imrank340@gmail.com
*   Organization:  Onami Systems Ltd
*
* =========================================================================
*/

#ifndef ADF_COLORS_H
#define ADF_COLORS_H


/* make it pretty  */
#define lblack      "\033[0;30m"     /* Black  normal */
#define lblue       "\033[0;34m"     /* Blue          */
#define lgreen      "\033[0;32m"     /* Green         */
#define lcyan       "\033[0;36m"     /* Cyan          */
#define lred        "\033[0;31m"     /* Red           */
#define lpurple     "\033[0;35m"     /* Purple normal */
#define lbrown      "\033[0;33m"     /* Brown         */
#define lgray       "\033[0;37m"     /* Gray          */
/*
 * conflict between XLib X11 and AMSI code 
 * therefore, used nred, ngreen
 */

#define nred       "\033[1;31m"     /* 0 -> normal ;  31 -> red */
#define cyan       "\033[1;36m"     /* 1 -> bold ;    36 -> cyan */
#define ngreen     "\033[1;32m"     /* 4 -> underline;32 -> green */
#define nblue      "\033[1;34m"     /* 9 -> strike ;  34 -> blue */

#define black      "\033[1;30m"
#define brown      "\033[1;33m"
#define magenta    "\033[1;35m"
#define gray       "\033[1;37m"
#define white      "\033[1;37m"      /* White color on the Black */
#define yellow     "\033[1;33m"

#define cls        "\033[2J\033[1;1H"   /* Clear the screen */

#define none       "\033[0m"            /* to flush the previous property */


#define onpurple     "\033[45m"          /* Background colors */
#define onblack      "\033[40m"          /* Black background */
#define onred        "\033[41m"          /* on the Red */
#define ongreen      "\033[42m"          /* on green   */
#define onyellow     "\033[43m"          /* on yellow  */
#define onblue       "\033[44m"          /* on blue    */
#define oncyan       "\033[46m"          /* on cyan    */
#define onwhite      "\033[47m"          /* on white   */

/* 88/256 colors
 * =============
 *
 * Some terminals can support 88 or 256 color. Here are the out 
 * sequence that permit you to use them
 *
 * The color number 256 is only supported by the vt0 terminal XFCE4
 * Terminal. 
 *
 * For using the 256 color on foreground the control sequences:
 *    "<ESC>[38;5;ColorNumberm"
 */

#define _01_	"\033[38;5;1m"
#define _02_	"\033[38;5;2m"
#define _03_	"\033[38;5;3m"
#define _04_	"\033[38;5;4m"
#define _05_	"\033[38;5;5m"
#define _06_	"\033[38;5;6m"
#define _07_	"\033[38;5;7m"
#define _08_	"\033[38;5;8m"
#define _09_	"\033[38;5;9m"
#define _010_	"\033[38;5;10m"
#define _011_	"\033[38;5;11m"
#define _012_	"\033[38;5;12m"
#define _013_	"\033[38;5;13m"
#define _014_	"\033[38;5;14m"
#define _015_	"\033[38;5;15m"
#define _016_	"\033[38;5;16m"
#define _017_	"\033[38;5;17m"
#define _018_	"\033[38;5;18m"
#define _019_	"\033[38;5;19m"
#define _020_	"\033[38;5;20m"
#define _021_	"\033[38;5;21m"
#define _022_	"\033[38;5;22m"
#define _023_	"\033[38;5;23m"
#define _024_	"\033[38;5;24m"
#define _025_	"\033[38;5;25m"
#define _026_	"\033[38;5;26m"
#define _027_	"\033[38;5;27m"
#define _028_	"\033[38;5;28m"
#define _029_	"\033[38;5;29m"
#define _030_	"\033[38;5;30m"
#define _031_	"\033[38;5;31m"
#define _032_	"\033[38;5;32m"
#define _033_	"\033[38;5;33m"
#define _034_	"\033[38;5;34m"
#define _035_	"\033[38;5;35m"
#define _036_	"\033[38;5;36m"
#define _037_	"\033[38;5;37m"
#define _038_	"\033[38;5;38m"
#define _039_	"\033[38;5;39m"
#define _040_	"\033[38;5;40m"
#define _041_	"\033[38;5;41m"
#define _042_	"\033[38;5;42m"
#define _043_	"\033[38;5;43m"
#define _044_	"\033[38;5;44m"
#define _045_	"\033[38;5;45m"
#define _046_	"\033[38;5;46m"
#define _047_	"\033[38;5;47m"
#define _048_	"\033[38;5;48m"
#define _049_	"\033[38;5;49m"
#define _050_	"\033[38;5;50m"
#define _051_	"\033[38;5;51m"
#define _052_	"\033[38;5;52m"
#define _053_	"\033[38;5;53m"
#define _054_	"\033[38;5;54m"
#define _055_	"\033[38;5;55m"
#define _056_	"\033[38;5;56m"
#define _057_	"\033[38;5;57m"
#define _058_	"\033[38;5;58m"
#define _059_	"\033[38;5;59m"
#define _060_	"\033[38;5;60m"
#define _061_	"\033[38;5;61m"
#define _062_	"\033[38;5;62m"
#define _063_	"\033[38;5;63m"
#define _064_	"\033[38;5;64m"
#define _065_	"\033[38;5;65m"
#define _066_	"\033[38;5;66m"
#define _067_	"\033[38;5;67m"
#define _068_	"\033[38;5;68m"
#define _069_	"\033[38;5;69m"
#define _070_	"\033[38;5;70m"
#define _071_	"\033[38;5;71m"
#define _072_	"\033[38;5;72m"
#define _073_	"\033[38;5;73m"
#define _074_	"\033[38;5;74m"
#define _075_	"\033[38;5;75m"
#define _076_	"\033[38;5;76m"
#define _077_	"\033[38;5;77m"
#define _078_	"\033[38;5;78m"
#define _079_	"\033[38;5;79m"
#define _080_	"\033[38;5;80m"
#define _081_	"\033[38;5;81m"
#define _082_	"\033[38;5;82m"
#define _083_	"\033[38;5;83m"
#define _084_	"\033[38;5;84m"
#define _085_	"\033[38;5;85m"
#define _086_	"\033[38;5;86m"
#define _087_	"\033[38;5;87m"
#define _088_	"\033[38;5;88m"
#define _089_	"\033[38;5;89m"
#define _090_	"\033[38;5;90m"
#define _091_	"\033[38;5;91m"
#define _092_	"\033[38;5;92m"
#define _093_	"\033[38;5;93m"
#define _094_	"\033[38;5;94m"
#define _095_	"\033[38;5;95m"
#define _096_	"\033[38;5;96m"
#define _097_	"\033[38;5;97m"
#define _098_	"\033[38;5;98m"
#define _099_	"\033[38;5;99m"
#define _0100_	"\033[38;5;100m"
#define _0101_	"\033[38;5;101m"
#define _0102_	"\033[38;5;102m"
#define _0103_	"\033[38;5;103m"
#define _0104_	"\033[38;5;104m"
#define _0105_	"\033[38;5;105m"
#define _0106_	"\033[38;5;106m"
#define _0107_	"\033[38;5;107m"
#define _0108_	"\033[38;5;108m"
#define _0109_	"\033[38;5;109m"
#define _0110_	"\033[38;5;110m"
#define _0111_	"\033[38;5;111m"
#define _0112_	"\033[38;5;112m"
#define _0113_	"\033[38;5;113m"
#define _0114_	"\033[38;5;114m"
#define _0115_	"\033[38;5;115m"
#define _0116_	"\033[38;5;116m"
#define _0117_	"\033[38;5;117m"
#define _0118_	"\033[38;5;118m"
#define _0119_	"\033[38;5;119m"
#define _0120_	"\033[38;5;120m"
#define _0121_	"\033[38;5;121m"
#define _0122_	"\033[38;5;122m"
#define _0123_	"\033[38;5;123m"
#define _0124_	"\033[38;5;124m"
#define _0125_	"\033[38;5;125m"
#define _0126_	"\033[38;5;126m"
#define _0127_	"\033[38;5;127m"
#define _0128_	"\033[38;5;128m"
#define _0129_	"\033[38;5;129m"
#define _0130_	"\033[38;5;130m"
#define _0131_	"\033[38;5;131m"
#define _0132_	"\033[38;5;132m"
#define _0133_	"\033[38;5;133m"
#define _0134_	"\033[38;5;134m"
#define _0135_	"\033[38;5;135m"
#define _0136_	"\033[38;5;136m"
#define _0137_	"\033[38;5;137m"
#define _0138_	"\033[38;5;138m"
#define _0139_	"\033[38;5;139m"
#define _0140_	"\033[38;5;140m"
#define _0141_	"\033[38;5;141m"
#define _0142_	"\033[38;5;142m"
#define _0143_	"\033[38;5;143m"
#define _0144_	"\033[38;5;144m"
#define _0145_	"\033[38;5;145m"
#define _0146_	"\033[38;5;146m"
#define _0147_	"\033[38;5;147m"
#define _0148_	"\033[38;5;148m"
#define _0149_	"\033[38;5;149m"
#define _0150_	"\033[38;5;150m"
#define _0151_	"\033[38;5;151m"
#define _0152_	"\033[38;5;152m"
#define _0153_	"\033[38;5;153m"
#define _0154_	"\033[38;5;154m"
#define _0155_	"\033[38;5;155m"
#define _0156_	"\033[38;5;156m"
#define _0157_	"\033[38;5;157m"
#define _0158_	"\033[38;5;158m"
#define _0159_	"\033[38;5;159m"
#define _0160_	"\033[38;5;160m"
#define _0161_	"\033[38;5;161m"
#define _0162_	"\033[38;5;162m"
#define _0163_	"\033[38;5;163m"
#define _0164_	"\033[38;5;164m"
#define _0165_	"\033[38;5;165m"
#define _0166_	"\033[38;5;166m"
#define _0167_	"\033[38;5;167m"
#define _0168_	"\033[38;5;168m"
#define _0169_	"\033[38;5;169m"
#define _0170_	"\033[38;5;170m"
#define _0171_	"\033[38;5;171m"
#define _0172_	"\033[38;5;172m"
#define _0173_	"\033[38;5;173m"
#define _0174_	"\033[38;5;174m"
#define _0175_	"\033[38;5;175m"
#define _0176_	"\033[38;5;176m"
#define _0177_	"\033[38;5;177m"
#define _0178_	"\033[38;5;178m"
#define _0179_	"\033[38;5;179m"
#define _0180_	"\033[38;5;180m"
#define _0181_	"\033[38;5;181m"
#define _0182_	"\033[38;5;182m"
#define _0183_	"\033[38;5;183m"
#define _0184_	"\033[38;5;184m"
#define _0185_	"\033[38;5;185m"
#define _0186_	"\033[38;5;186m"
#define _0187_	"\033[38;5;187m"
#define _0188_	"\033[38;5;188m"
#define _0189_	"\033[38;5;189m"
#define _0190_	"\033[38;5;190m"
#define _0191_	"\033[38;5;191m"
#define _0192_	"\033[38;5;192m"
#define _0193_	"\033[38;5;193m"
#define _0194_	"\033[38;5;194m"
#define _0195_	"\033[38;5;195m"
#define _0196_	"\033[38;5;196m"
#define _0197_	"\033[38;5;197m"
#define _0198_	"\033[38;5;198m"
#define _0199_	"\033[38;5;199m"
#define _0200_	"\033[38;5;200m"
#define _0201_	"\033[38;5;201m"
#define _0202_	"\033[38;5;202m"
#define _0203_	"\033[38;5;203m"
#define _0204_	"\033[38;5;204m"
#define _0205_	"\033[38;5;205m"
#define _0206_	"\033[38;5;206m"
#define _0207_	"\033[38;5;207m"
#define _0208_	"\033[38;5;208m"
#define _0209_	"\033[38;5;209m"
#define _0210_	"\033[38;5;210m"
#define _0211_	"\033[38;5;211m"
#define _0212_	"\033[38;5;212m"
#define _0213_	"\033[38;5;213m"
#define _0214_	"\033[38;5;214m"
#define _0215_	"\033[38;5;215m"
#define _0216_	"\033[38;5;216m"
#define _0217_	"\033[38;5;217m"
#define _0218_	"\033[38;5;218m"
#define _0219_	"\033[38;5;219m"
#define _0220_	"\033[38;5;220m"
#define _0221_	"\033[38;5;221m"
#define _0222_	"\033[38;5;222m"
#define _0223_	"\033[38;5;223m"
#define _0224_	"\033[38;5;224m"
#define _0225_	"\033[38;5;225m"
#define _0226_	"\033[38;5;226m"
#define _0227_	"\033[38;5;227m"
#define _0228_	"\033[38;5;228m"
#define _0229_	"\033[38;5;229m"
#define _0230_	"\033[38;5;230m"
#define _0231_	"\033[38;5;231m"
#define _0232_	"\033[38;5;232m"
#define _0233_	"\033[38;5;233m"
#define _0234_	"\033[38;5;234m"
#define _0235_	"\033[38;5;235m"
#define _0236_	"\033[38;5;236m"
#define _0237_	"\033[38;5;237m"
#define _0238_	"\033[38;5;238m"
#define _0239_	"\033[38;5;239m"
#define _0240_	"\033[38;5;240m"
#define _0241_	"\033[38;5;241m"
#define _0242_	"\033[38;5;242m"
#define _0243_	"\033[38;5;243m"
#define _0244_	"\033[38;5;244m"
#define _0245_	"\033[38;5;245m"
#define _0246_	"\033[38;5;246m"
#define _0247_	"\033[38;5;247m"
#define _0248_	"\033[38;5;248m"
#define _0249_	"\033[38;5;249m"
#define _0250_	"\033[38;5;250m"
#define _0251_	"\033[38;5;251m"
#define _0252_	"\033[38;5;252m"
#define _0253_	"\033[38;5;253m"
#define _0254_	"\033[38;5;254m"
#define _0255_	"\033[38;5;255m"
#define _0256_	"\033[38;5;256m"


/* Background Color scheme codes */
/* ============================= */

#define _001_	"\033[48;5;1m"
#define _002_	"\033[48;5;2m"
#define _003_	"\033[48;5;3m"
#define _004_	"\033[48;5;4m"
#define _005_	"\033[48;5;5m"
#define _006_	"\033[48;5;6m"
#define _007_	"\033[48;5;7m"
#define _008_	"\033[48;5;8m"
#define _009_	"\033[48;5;9m"
#define _0010_	"\033[48;5;10m"
#define _0011_	"\033[48;5;11m"
#define _0012_	"\033[48;5;12m"
#define _0013_	"\033[48;5;13m"
#define _0014_	"\033[48;5;14m"
#define _0015_	"\033[48;5;15m"
#define _0016_	"\033[48;5;16m"
#define _0017_	"\033[48;5;17m"
#define _0018_	"\033[48;5;18m"
#define _0019_	"\033[48;5;19m"
#define _0020_	"\033[48;5;20m"
#define _0021_	"\033[48;5;21m"
#define _0022_	"\033[48;5;22m"
#define _0023_	"\033[48;5;23m"
#define _0024_	"\033[48;5;24m"
#define _0025_	"\033[48;5;25m"
#define _0026_	"\033[48;5;26m"
#define _0027_	"\033[48;5;27m"
#define _0028_	"\033[48;5;28m"
#define _0029_	"\033[48;5;29m"
#define _0030_	"\033[48;5;30m"
#define _0031_	"\033[48;5;31m"
#define _0032_	"\033[48;5;32m"
#define _0033_	"\033[48;5;33m"
#define _0034_	"\033[48;5;34m"
#define _0035_	"\033[48;5;35m"
#define _0036_	"\033[48;5;36m"
#define _0037_	"\033[48;5;37m"
#define _0038_	"\033[48;5;38m"
#define _0039_	"\033[48;5;39m"
#define _0040_	"\033[48;5;40m"
#define _0041_	"\033[48;5;41m"
#define _0042_	"\033[48;5;42m"
#define _0043_	"\033[48;5;43m"
#define _0044_	"\033[48;5;44m"
#define _0045_	"\033[48;5;45m"
#define _0046_	"\033[48;5;46m"
#define _0047_	"\033[48;5;47m"
#define _0048_	"\033[48;5;48m"
#define _0049_	"\033[48;5;49m"
#define _0050_	"\033[48;5;50m"
#define _0051_	"\033[48;5;51m"
#define _0052_	"\033[48;5;52m"
#define _0053_	"\033[48;5;53m"
#define _0054_	"\033[48;5;54m"
#define _0055_	"\033[48;5;55m"
#define _0056_	"\033[48;5;56m"
#define _0057_	"\033[48;5;57m"
#define _0058_	"\033[48;5;58m"
#define _0059_	"\033[48;5;59m"
#define _0060_	"\033[48;5;60m"
#define _0061_	"\033[48;5;61m"
#define _0062_	"\033[48;5;62m"
#define _0063_	"\033[48;5;63m"
#define _0064_	"\033[48;5;64m"
#define _0065_	"\033[48;5;65m"
#define _0066_	"\033[48;5;66m"
#define _0067_	"\033[48;5;67m"
#define _0068_	"\033[48;5;68m"
#define _0069_	"\033[48;5;69m"
#define _0070_	"\033[48;5;70m"
#define _0071_	"\033[48;5;71m"
#define _0072_	"\033[48;5;72m"
#define _0073_	"\033[48;5;73m"
#define _0074_	"\033[48;5;74m"
#define _0075_	"\033[48;5;75m"
#define _0076_	"\033[48;5;76m"
#define _0077_	"\033[48;5;77m"
#define _0078_	"\033[48;5;78m"
#define _0079_	"\033[48;5;79m"
#define _0080_	"\033[48;5;80m"
#define _0081_	"\033[48;5;81m"
#define _0082_	"\033[48;5;82m"
#define _0083_	"\033[48;5;83m"
#define _0084_	"\033[48;5;84m"
#define _0085_	"\033[48;5;85m"
#define _0086_	"\033[48;5;86m"
#define _0087_	"\033[48;5;87m"
#define _0088_	"\033[48;5;88m"
#define _0089_	"\033[48;5;89m"
#define _0090_	"\033[48;5;90m"
#define _0091_	"\033[48;5;91m"
#define _0092_	"\033[48;5;92m"
#define _0093_	"\033[48;5;93m"
#define _0094_	"\033[48;5;94m"
#define _0095_	"\033[48;5;95m"
#define _0096_	"\033[48;5;96m"
#define _0097_	"\033[48;5;97m"
#define _0098_	"\033[48;5;98m"
#define _0099_	"\033[48;5;99m"
#define _00100_	"\033[48;5;100m"
#define _00101_	"\033[48;5;101m"
#define _00102_	"\033[48;5;102m"
#define _00103_	"\033[48;5;103m"
#define _00104_	"\033[48;5;104m"
#define _00105_	"\033[48;5;105m"
#define _00106_	"\033[48;5;106m"
#define _00107_	"\033[48;5;107m"
#define _00108_	"\033[48;5;108m"
#define _00109_	"\033[48;5;109m"
#define _00110_	"\033[48;5;110m"
#define _00111_	"\033[48;5;111m"
#define _00112_	"\033[48;5;112m"
#define _00113_	"\033[48;5;113m"
#define _00114_	"\033[48;5;114m"
#define _00115_	"\033[48;5;115m"
#define _00116_	"\033[48;5;116m"
#define _00117_	"\033[48;5;117m"
#define _00118_	"\033[48;5;118m"
#define _00119_	"\033[48;5;119m"
#define _00120_	"\033[48;5;120m"
#define _00121_	"\033[48;5;121m"
#define _00122_	"\033[48;5;122m"
#define _00123_	"\033[48;5;123m"
#define _00124_	"\033[48;5;124m"
#define _00125_	"\033[48;5;125m"
#define _00126_	"\033[48;5;126m"
#define _00127_	"\033[48;5;127m"
#define _00128_	"\033[48;5;128m"
#define _00129_	"\033[48;5;129m"
#define _00130_	"\033[48;5;130m"
#define _00131_	"\033[48;5;131m"
#define _00132_	"\033[48;5;132m"
#define _00133_	"\033[48;5;133m"
#define _00134_	"\033[48;5;134m"
#define _00135_	"\033[48;5;135m"
#define _00136_	"\033[48;5;136m"
#define _00137_	"\033[48;5;137m"
#define _00138_	"\033[48;5;138m"
#define _00139_	"\033[48;5;139m"
#define _00140_	"\033[48;5;140m"
#define _00141_	"\033[48;5;141m"
#define _00142_	"\033[48;5;142m"
#define _00143_	"\033[48;5;143m"
#define _00144_	"\033[48;5;144m"
#define _00145_	"\033[48;5;145m"
#define _00146_	"\033[48;5;146m"
#define _00147_	"\033[48;5;147m"
#define _00148_	"\033[48;5;148m"
#define _00149_	"\033[48;5;149m"
#define _00150_	"\033[48;5;150m"
#define _00151_	"\033[48;5;151m"
#define _00152_	"\033[48;5;152m"
#define _00153_	"\033[48;5;153m"
#define _00154_	"\033[48;5;154m"
#define _00155_	"\033[48;5;155m"
#define _00156_	"\033[48;5;156m"
#define _00157_	"\033[48;5;157m"
#define _00158_	"\033[48;5;158m"
#define _00159_	"\033[48;5;159m"
#define _00160_	"\033[48;5;160m"
#define _00161_	"\033[48;5;161m"
#define _00162_	"\033[48;5;162m"
#define _00163_	"\033[48;5;163m"
#define _00164_	"\033[48;5;164m"
#define _00165_	"\033[48;5;165m"
#define _00166_	"\033[48;5;166m"
#define _00167_	"\033[48;5;167m"
#define _00168_	"\033[48;5;168m"
#define _00169_	"\033[48;5;169m"
#define _00170_	"\033[48;5;170m"
#define _00171_	"\033[48;5;171m"
#define _00172_	"\033[48;5;172m"
#define _00173_	"\033[48;5;173m"
#define _00174_	"\033[48;5;174m"
#define _00175_	"\033[48;5;175m"
#define _00176_	"\033[48;5;176m"
#define _00177_	"\033[48;5;177m"
#define _00178_	"\033[48;5;178m"
#define _00179_	"\033[48;5;179m"
#define _00180_	"\033[48;5;180m"
#define _00181_	"\033[48;5;181m"
#define _00182_	"\033[48;5;182m"
#define _00183_	"\033[48;5;183m"
#define _00184_	"\033[48;5;184m"
#define _00185_	"\033[48;5;185m"
#define _00186_	"\033[48;5;186m"
#define _00187_	"\033[48;5;187m"
#define _00188_	"\033[48;5;188m"
#define _00189_	"\033[48;5;189m"
#define _00190_	"\033[48;5;190m"
#define _00191_	"\033[48;5;191m"
#define _00192_	"\033[48;5;192m"
#define _00193_	"\033[48;5;193m"
#define _00194_	"\033[48;5;194m"
#define _00195_	"\033[48;5;195m"
#define _00196_	"\033[48;5;196m"
#define _00197_	"\033[48;5;197m"
#define _00198_	"\033[48;5;198m"
#define _00199_	"\033[48;5;199m"
#define _00200_	"\033[48;5;200m"
#define _00201_	"\033[48;5;201m"
#define _00202_	"\033[48;5;202m"
#define _00203_	"\033[48;5;203m"
#define _00204_	"\033[48;5;204m"
#define _00205_	"\033[48;5;205m"
#define _00206_	"\033[48;5;206m"
#define _00207_	"\033[48;5;207m"
#define _00208_	"\033[48;5;208m"
#define _00209_	"\033[48;5;209m"
#define _00210_	"\033[48;5;210m"
#define _00211_	"\033[48;5;211m"
#define _00212_	"\033[48;5;212m"
#define _00213_	"\033[48;5;213m"
#define _00214_	"\033[48;5;214m"
#define _00215_	"\033[48;5;215m"
#define _00216_	"\033[48;5;216m"
#define _00217_	"\033[48;5;217m"
#define _00218_	"\033[48;5;218m"
#define _00219_	"\033[48;5;219m"
#define _00220_	"\033[48;5;220m"
#define _00221_	"\033[48;5;221m"
#define _00222_	"\033[48;5;222m"
#define _00223_	"\033[48;5;223m"
#define _00224_	"\033[48;5;224m"
#define _00225_	"\033[48;5;225m"
#define _00226_	"\033[48;5;226m"
#define _00227_	"\033[48;5;227m"
#define _00228_	"\033[48;5;228m"
#define _00229_	"\033[48;5;229m"
#define _00230_	"\033[48;5;230m"
#define _00231_	"\033[48;5;231m"
#define _00232_	"\033[48;5;232m"
#define _00233_	"\033[48;5;233m"
#define _00234_	"\033[48;5;234m"
#define _00235_	"\033[48;5;235m"
#define _00236_	"\033[48;5;236m"
#define _00237_	"\033[48;5;237m"
#define _00238_	"\033[48;5;238m"
#define _00239_	"\033[48;5;239m"
#define _00240_	"\033[48;5;240m"
#define _00241_	"\033[48;5;241m"
#define _00242_	"\033[48;5;242m"
#define _00243_	"\033[48;5;243m"
#define _00244_	"\033[48;5;244m"
#define _00245_	"\033[48;5;245m"
#define _00246_	"\033[48;5;246m"
#define _00247_	"\033[48;5;247m"
#define _00248_	"\033[48;5;248m"
#define _00249_	"\033[48;5;249m"
#define _00250_	"\033[48;5;250m"
#define _00251_	"\033[48;5;251m"
#define _00252_	"\033[48;5;252m"
#define _00253_	"\033[48;5;253m"
#define _00254_	"\033[48;5;254m"
#define _00255_	"\033[48;5;255m"
#define _00256_	"\033[48;5;256m"

                /* X11 Org Colors listing */
                /*========================*/

#define Alice_Blue	        "#F0F8FF" // 94%97%	100%208° 100% 97% 6% 100%
#define Antique_White       "#FAEBD7" // 98% 92% 84% 34° 78% 91% 14% 98%
#define Aqua                "#00FFFF" // 0% 100%100% 180° 100%50%100%100%Cyan
#define Aquamarine	        "#7FFFD4" //	50%	100% 83% 160° 100%	75%	50%	100%
#define Azure	            "#F0FFFF" //94%	100% 100% 180°100%97%6%	100%
#define Beige	            "#F5F5DC" //	96%	96%	86%	60°	56%	91%	10%	96%
#define Bisque	            "#FFE4C4" //100%89%	77%	33°	100%88%	23%	100%
#define Black	            "#000000" //	0%	0%	0%	0°	0%	0%	0%	0%
#define Blanched_Almond     "#FFEBCD" // 100% 92% 80% 36° 100% 90% 20% 100%
#define Blue	            "#0000FF" //0%0%100% 240° 100%	50%	100% 100%
#define Blue_Violet	        "#8A2BE2" //	54%	17%	89%	271°	76%	53%	81%	89%
#define Brown	            "#A52A2A" //	65%	16%	16%	0°	59%	41%	75%	65%
#define Burlywood	        "#DEB887" // 87%	72%	53%	34°	57%	70%	39%	87%
#define Cadet Blue	        "#5F9EA0" //	37%	62%	63%	182°	26%	50%	41%	63%
#define Chartreuse	        "#7FFF00" //	50%	100% 0%	90°	100% 50% 100% 100%
#define Chocolate	        "#D2691E" //	82%	41%	12%	25°	75%	47%	86%	82%
#define Coral	            "#FF7F50" //100%50%	31%	16°	100%66%	69%	100%
#define Cornflower_Blue     "#6495ED" //39%	58%	93%	219°	79%	66%	58%	93%
#define Cornsilk	        "#FFF8DC" // 100%	97%	86%	48°	100%	93%	14%	100%
#define Crimson	            "#DC143C" // 86%	8%	24%	348°	83%	47%	91%	86%
#define Cyan	            "#00FFFF" //0%100% 100% 180°100% 50% 100% 100% Aqua
#define Dark_Blue	        "#00008B" // 0%	0%	55%	240° 100% 27% 100% 55%
#define Dark_Cyan	        "#008B8B" //	0%	55%	55%	180° 100% 27% 100%	55%
#define Dark_Goldenrod      "#B8860B" //	72%	53%	4%	43°	89%	38%	94%	72%
#define Dark_GrayL	        "#A9A9A9" //66%	66%	66%	0° 0% 66% 0% 66% Dark Grey
#define Dark_Green	        "#006400" // 0%	39%	0%	120° 100% 20% 100% 39%
#define Dark_Khaki	        "#BDB76B" //	74%	72%	42%	56°	38%	58%	43%	74%
#define Dark_Magenta        "#8B008B" //  55% 0%	55%	300° 100% 27% 100%	55%
#define Dark_Olive_Green	"#556B2F" // 33%	42%	18%	82°	39%	30%	56%	42%
#define Dark_Orange	        "#FF8C00" // 100% 55% 0%	33°	100% 50% 100% 100%
#define Dark_Orchid	        "#9932CC" //	60%	20%	80%	280°	61%	50%	75%	80%
#define Dark_Red	        "#8B0000" // 55%	0%	0%	0°	100% 27% 100% 55%
#define Dark_Salmon	        "#E9967A" // 91%	59%	48%	15°	72%	70%	48%	91%
#define Dark_Sea_Green      "#8FBC8F" //56%	74%	56%	120° 25% 65%	24%	74%
#define Dark_Slate_Blue	    "#483D8B" //	28%	24%	55%	248°	39%	39%	56%	55%
#define Dark_Slate_Gray	    "#2F4F4F" //	18%	31%	31%	180°25%	25%	41%	31%	
#define Dark_Turquoise	    "#00CED1" //	0%	81%	82%	181° 100% 41%100% 82%
#define Dark_Violet	        "#9400D3" //	58%	0%	83%	282° 100% 41% 100%	83%
#define Deep_Pink	        "#FF1493" //	100% 8%	58%	328° 100% 54% 92% 100%
#define Deep_Sky_Blue	    "#00BFFF" //	0%	75%	100% 195° 100% 50% 100%	100%
#define Dim_Gray	        "#696969" //41%	41%	41%	0°	0%	41%	0%	41%	Dim Grey
#define Dodger_Blue	        "#1E90FF" //	12%	56%	100% 210° 100%	56%	88%	100%
#define Firebrick	        "#B22222" //	70%	13%	13%	0°	68%	42%	81%	70%
#define Floral_White        "#FFFAF0" //  100% 98% 94% 40° 100%	97%	6%	100%
#define Forest_Green	    "#228B22" //	13%	55%	13%	120°	61%	34%	76%	55%
#define Fuchsia	            "#FF00FF" // 100% 0%100% 300°100%50%100%100%Magenta
#define Gainsboro	        "#DCDCDC" //	86%	86%	86%	0°	0%	86%	0%	86%
#define Ghost_White	        "#F8F8FF" //	97%	97%	100% 240° 100%	99%	3%	100%
#define Gold	            "#FFD700" //100%	84%	0%	51°	100% 50% 100% 100%
#define Goldenrod	        "#DAA520" //	85%	65%	13%	43°	74%	49%	85%	85%
#define Gray                "#BEBEBE" //  75% 75% 75% 0° 0%	75%	0% 75% X11 
#define Web_Gray            "#808080" // 50% 50% 50% 0°	0%	50%	0%	50%	y
#define GreenL              "#00FF00" // 0%100%0% 120° 100% 50% 100% 100% 
#define Web_Green           "#008000" // 0% 50% 0%	120° 100% 25% 100%	50%
#define Green_Yellow        "#ADFF2F" // 68% 100% 18% 84° 100%	59%	82%	100%
#define Honeydew            "#F0FFF0" //  94% 100% 94% 120° 100%	97%	6%	100%
#define Hot_Pink	        "#FF69B4" // 100% 41% 71% 330° 100%	71%	59%	100%
#define Indian_Red	        "#CD5C5C" // 80%	36%	36%	0°	53%	58%	55%	80%
#define Indigo	            "#4B0082" // 29% 0%	51%	275° 100% 26% 100%	51%
#define Ivory	            "#FFFFF0" // 100%	100% 94% 60° 100% 97% 6% 100%
#define Khaki	            "#F0E68C" // 94%	90%	55%	54°	77%	75%	42%	94%
#define Lavender	        "#E6E6FA" // 90%	90%	98%	240°	67%	94%	8%	98%
#define Lavender_Blush	    "#FFF0F5" // 100% 94% 96% 340° 100% 97% 6% 100%
#define Lawn_Green	        "#7CFC00" // 49% 99% 0%	90°	100% 49%	100%	99%
#define Lemon_Chiffon       "#FFFACD" // 100%	98%	80%	54°	100% 90% 20% 100%
#define Light_Blue	        "#ADD8E6" //	68%	85%	90%	195°	53%	79%	25%	90%
#define Light_Coral	        "#F08080" //	94%	50%	50%	0°	79%	72%	47%	94%
#define Light_Cyan	        "#E0FFFF" //	88%	100% 100% 180° 100%	94%	12%	100%
#define Light_Goldenrod	    "#FAFAD2" //	98%	98%	82%	60°	80%	90%	16%	98%
#define Light_Gray          "#D3D3D3" //83%	83%	83%	0° 0% 83% 0%83%	Light Grey
#define Light_Green	        "#90EE90" //	56%	93%	56%	120°	73%	75%	39%	93%
#define Light_Pink	        "#FFB6C1" //	100% 71% 76% 351° 100%	86%	29%	100%
#define Light_Salmon        "#FFA07A" // 100% 63% 48% 17° 100%	74%	52%	100%
#define Light_Sea_Green	    "#20B2AA" //	13%	70%	67%	177°	70%	41%	82%	70%
#define Light_Sky_Blue	    "#87CEFA" //	53%	81%	98%	203°	92%	76%	46%	98%
#define Light_Slate_Gray    "#778899" // 47% 53% 60% 210°14% 53% 22% 60% 
#define Light_Steel_Blue    "#B0C4DE" // 69% 77% 87% 214° 41% 78% 21%87%
#define Light_Yellow        "#FFFFE0" // 100% 100%	88%	60°	100% 94%	12%	100%
#define Lime                "#00FF00" // 0%	100% 0%	120° 100%	50%	100%	100%
#define Lime_Green	        "#32CD32" //	20%	80%	20%	120°	61%	50%	76%	80%
#define Linen	            "#FAF0E6" //	98%	94%	90%	30°	67%	94%	8%	98%
#define Magenta	            "#FF00FF" // 100% 0% 100% 300° 100% 50% 100% 100%
#define Maroon	            "#B03060" // 69%19%	38%	338° 57% 44% 73% 69% X11 
#define Web_Maroon	        "#800000" // 50% 0%	0%	0°	100% 25% 100% 50%
#define Medium_Aquamarine	"#66CDAA" //	40%	80%	67%	160°51%	60%	50%	80%
#define Medium_Blue	        "#0000CD" //	0%	0%	80%	240° 100% 40% 100%	80%
#define Medium_Orchid	    "#BA55D3" //	73%	33%	83%	288°	59%	58%	60%	83%
#define Medium_Purple	    "#9370DB" //	58%	44%	86%	260°	60%	65%	49%	86%
#define Medium_Sea_Green    "#3CB371" // 24% 70% 44%	147° 50%47%	66%	70%
#define Medium_Slate_Blue   "#7B68EE" // 48% 41% 93% 249°	80%	67%	56%	93%
#define Medium_Spring_Green	"#00FA9A" // 0% 98% 60% 157°	100% 49%100%98%
#define Medium_Turquoise    "#48D1CC" // 28% 82% 80% 178° 60% 55% 66% 82%
#define Medium_Violet Red   "#C71585" // 78% 8% 52% 322° 81% 43% 89% 78%
#define Midnight_Blue	    "#191970" //10%	10%	44%	240°	64%	27%	78%	44%
#define Mint_Cream	        "#F5FFFA" //96%	100% 98% 150° 100%	98%	4%	100%
#define Misty_Rose	        "#FFE4E1" //100%	89%	88%	6°	100%	94%	12%	100%
#define Moccasin	        "#FFE4B5" //100%	89%	71%	38°	100%	86%	29%	100%
#define Navajo_White        "#FFDEAD" // 100%	87%	68%	36°	100%	84%	32%	100%
#define Navy_Blue           "#000080" // 0% 0%	50%	240° 100%25% 100%	50%	Navy
#define Old_Lace	        "#FDF5E6" // 99%	96%	90%	39°	85%	95%	9%	99%
#define Olive	            "#808000" // 50% 50%	0%	60°	100% 25% 100% 50%
#define Olive_Drab	        "#6B8E23" //	42%	56%	14%	80°	61%	35%	75%	56%
#define Orange	            "#FFA500" // 100%	65%	0%	39°	100% 50% 100% 100%
#define Orange_Red	        "#FF4500" //	100% 27% 0%	16°	100% 50% 100%	100%
#define Orchid	            "#DA70D6" //	85%	44%	84%	302°	59%	65%	49%	85%
#define Pale_Goldenrod	    "#EEE8AA" // 93%	91%	67%	55°	67%	80%	29%	93%
#define Pale_Green	        "#98FB98" //	60%	98%	60%	120°	93%	79%	39%	98%
#define Pale_Turquoise	    "#AFEEEE" //	69%	93%	93%	180°	65%	81%	26%	93%
#define Pale_Violet_Red	    "#DB7093" //	86%	44%	58%	340°	60%	65%	49%	86%
#define Papaya_Whip 	    "#FFEFD5" //	100% 94% 84% 37° 100% 92% 16% 100%
#define Peach_Puff	        "#FFDAB9" //	100% 85% 73%28°	100% 86% 27%100%
#define Peru	            "#CD853F" //	80%	52%	25%	30°	59%	53%	69%	80%
#define Pink	            "#FFC0CB" //	100% 75% 80% 350° 100%	88%	25%	100%
#define Plum	            "#DDA0DD" //	87%	63%	87%	300°	47%	75%	28%	87%
#define Powder_Blue	        "#B0E0E6" //	69%	88%	90%	187°	52%	80%	23%	90%
#define Purple	            "#A020F0" //	63%	13%	94%	277°87% 53% 87% 94% X11 
#define Web_Purple	        "#800080" //	50%	0%	50%	300° 100% 25% 100%	50%
#define Rebecca_Purple	    "#663399" //	40%	20%	60%	270°	50%	40%	67%	60%
#define Red	                "#FF0000" //	100%	0%	0%	0°	100% 50%100%100%
#define Rosy_Brown	        "#BC8F8F" //	74%	56%	56%	0°	25%	65%	24%	74%
#define Royal_Blue	        "#4169E1" //	25%	41%	88%	225°	73%	57%	71%	88%
#define Saddle_Brown	    "#8B4513" //	55%	27%	7%	25°	76%	31%	86%	55%
#define Salmon	            "#FA8072" //	98%	50%	45%	6°	93%	71%	54%	98%
#define Sandy_Brown	        "#F4A460" //	96%	64%	38%	28°	87%	67%	61%	96%
#define Sea_Green	        "#2E8B57" //	18%	55%	34%	146°	50%	36%	67%	55%
#define Seashell	        "#FFF5EE" //	100%96%	93%	25°	100% 97% 7%	100%
#define Sienna	            "#A0522D" //	63%	32%	18%	19°	56%	40%	72%	63%
#define Silver	            "#C0C0C0" //	75%	75%	75%	0°	0%	75%	0%	75%
#define Sky_Blue	        "#87CEEB" //	53%	81%	92%	197°	71%	73%	43%	92%
#define Slate_Blue	        "#6A5ACD" //	42%	35%	80%	248°	54%	58%	56%	80%
#define Slate_Gray          "#708090" // %50% 56% 210° 13% 50% 22%56% Slate Grey
#define Snow	            "#FFFAFA" //	100% 98% 98% 0°	100% 99% 2%	100%
#define Spring_Green        "#00FF7F" // 0%	100% 50% 150° 100% 50% 100%	100%
#define Steel_Blue	        "#4682B4" //	27%	51%	71%	207°	44%	49%	61%	71%
#define Tan	                "#D2B48C" //	82%	71%	55%	34°	44%	69%	33%	82%
#define Teal	            "#008080" //	0%	50%	50%	180° 100% 25% 100% 50%
#define Thistle	            "#D8BFD8" //	85%	75%	85%	300°	24%	80%	12%	85%
#define Tomato	            "#FF6347" //	100% 39% 28% 9°	100% 64% 72% 100%
#define Turquoise	        "#40E0D0" //	25%	88%	82%	174°	72%	57%	71%	88%
#define Violet	            "#EE82EE" //	93%	51%	93%	300°	76%	72%	45%	93%
#define Wheat	            "#F5DEB3" //	96%	87%	70%	39°	77%	83%	27%	96%
#define White	            "#FFFFFF" //	100% 100% 100% 0° 0% 100% 0%	100%
#define White_Smoke	        "#F5F5F5" //	96%	96%	96%	0°	0%	96%	0%	96%
#define Yellow	            "#FFFF00" //	100% 100% 0% 60° 100% 50% 100%	100%
#define Yellow_Green	    "#9ACD32" //	60%	80%	20%	80°	61%	50%	76%	80%

/*
   Examples:
    "Yellow 2" (238, 238, 0) is based on   "Yellow" (255, 255, 0) with 255 
    × 0.932 = 237.66.
    "Ivory 3" (205, 205, 193) is explained by   "Ivory" (255, 255, 240) where 
    255 × 0.804 = 205.02 and 240 × 0.804 = 192.96.
    "Azure 4" (131, 139, 139) is close to   "Azure" (240, 255, 255) values 
    transformed as 255 × 0.548 = 139.74 and 240 × 0.548 = 131.52.
    Named X11 colors with numbered variants (without grays)
*/
            /* X11 Org Color with W3SC code */
            /*==============================*/

#define Black	            "#000000" //	0% 0% 0% 0°	0%	0%	0%	0%	Black
#define Light_Black	        "#808080" //	50%	50%	50%	0°	0%	50%	0%	50%	
#define Blue                "#0000FF" //0%	0%100% 240°100% 50% 100%100% Blue 
#define Dark_Blue           "#00008B" // 0% 0% 55% 240° 100% 27% 100% 55% 
#define Light_Blue          "#ADD8E6" // 68% 85% 90% 195°53% 79% 25% 90%
#define Brown	            "#A52A2A" //	65%	16%	16%	0°	59%	41%	75%	65%	
#define Dark_Brown	        "#5C4033" //	36%	25%	20%	19°	29%	28%	45%	36%	
#define Light_Brown	        "#996600" //	60%	40%	0%	40°	100% 30% 100% 60%	
#define Buff	            "#F0DC82" //	94%	86%	51%	49°	79%	73%	46%	94%	
#define Dark_Buff	        "#976638" //	59%	40%	22%	29°	46%	41%	63%	59%	
#define Light_Buff	        "#ECD9B0" //	93%	85%	69%	41°	61%	81%	25%	93%	
#define Cyan                "#00FFFF" // 0%	100% 100% 180° 100%	50%	100% 100% 
#define Dark_Cyan           "#008B8B" // 0% 55% 55% 180° 100% 27% 100%	55%
#define Light_Cyan          "#E0FFFF" // 88% 100% 100% 180° 100%94%12% 100%
#define Gold	            "#FFD700" //	100% 84% 0%	51°	100%50%	100% 100% 
#define Dark_Gold	        "#EEBC1D" //	93%	74%	11%	46°	86%	52%	88%	93%	
#define Light_Gold	        "#F1E5AC" //	95%	90%	67%	50°	71%	81%	29%	95%	
#define Goldenrod	        "#DAA520" //	85%	65%	13%	43°	74%	49%	85%	86%	
#define Dark_Goldenrod	    "#B8860B" //	72%	53%	4%	43°	89%	38%	94%	72%	
#define Light_Goldenrode    "#FFEC8B" //	100% 93% 55% 50° 100% 77% 46% 100%
#define GrayL	            "#808080" //	50%	50%	50%	0°	0%	50%	0%	50%	
#define Dark_Gray	        "#404040" //  25%	25%	25%	0°	0%	25%	0%	25%	
#define Light_Gray	        "#D3D3D3" //	83%	83%	83%	0°	0%	83%	0%	83%	
#define Green	            "#008000" //	0%	50%	0%	120° 100% 25% 100%	50%
#define Dark_Green	        "#006400" //	0%	39%	0%	120°	100%	20%	100%
#define Light_Green	        "#90EE90" //	56%	93%	56%	120° 73% 75% 40% 93% 
#define Ivory	            "#FFFFF0" //	100% 100% 94% 60° 100%	97%	6% 100%
#define Dark_Ivory	        "#F2E58F" //	95%	90%	56%	52°	79%	76%	41%	95%	
#define Light_Ivory	        "#FFF8C9" //	100% 97% 79% 52° 100% 89% 21% 100%
#define Magenta	            "#FF00FF" //	100% 0%	100% 300° 100% 50% 100%100%
#define Dark_Magenta        "#8B008B" // 55% 0%	55%	300° 100% 27% 100% 55% 
#define Light_Magenta       "#FF77FF" // 100% 47% 100%	300° 100% 73% 53% 100%
#define Mustard	            "#FFDB58" // 100% 86% 35% 47° 100%	67%	66%	100%	
#define Dark_Mustard        "#7C7C40" // 49%	49%	25%	60°	32%	37%	48%	49%	
#define Light_Mustard	    "#EEDD62" //	93%	87%	38%	53°	81%	66%	59%	93%	
#define Orange	            "#FFA500" //	100% 65% 0%	39°	100% 50% 100% 100%
#define Dark_Orange	        "#FF8C00" //	100%55%	0% 33° 100%	50%	100% 100% 
#define Light_Orange        "#D9A465" //	85%	64%	40%	33°	60%	62%	54%	85%	
#define Pink	            "#FFC0CB" //	100% 75% 80% 350° 100% 88% 25% 100% 
#define Dark_Pink	        "#E75480" //	91%	33%	50%	342°	75%	62%	64%	91%	
#define Light_Pink	        "#FFB6C1" //	100% 71% 76% 351° 100% 86% 29% 100%	
#define Red	                "#FF0000" //	100% 0%	0%	0° 100% 50% 100% 100%
#define Dark_Red            "#8B0000" // 55% 0%	0%	0° 100%	27%	100% 55% 
#define Light_Red	        "#FF3333" //	100% 20% 20% 0°	100% 60% 80% 100%	
#define Silver	            "#C0C0C0" //	75%	75%	75%	0°	0%	75%	0%	75%	
#define Dark_Silver	        "#AFAFAF" //	69%	69%	69%	0°	0%	69%	0%	69%	
#define Light_Silver        "#E1E1E1" //	88%	88%	88%	0°	0%	88%	0%	88%	
#define TurquoiseL          "#30D5C8" // 19% 84% 78% 175° 66% 51%	78%	84%
#define Dark_Turquoise	    "#00CED1" //	0% 81%	82%	181° 100% 41% 100% 82%
#define Light_Turquoise	    "#AFE4DE" //	69%	89%	87%	173°	50%	79%	23%	89%	
#define Violet	            "#EE82EE" //	93%	51%	93%	300° 76%72%	45%	93%	
#define Dark_Violet	        "#9400D3" //	58%	0%	83%	282° 100% 41% 100%	83%	
#define Light_Violet        "#7A5299" //	48%	32%	60%	274°	30%	46%	46%	60%	
#define White	            "#FFFFFF" //	100% 100% 100% 0° 0% 100% 0% 100%  
#define Yellow	            "#FFFF00" //	100% 100% 0% 60°100% 50% 100% 100% 
#define Dark_Yellow	        "#FFCC00" //	100% 80% 0%	48°	100% 50% 100% 100%	
#define Light_Yellow        "#FFFFE0" //	100% 100% 88% 60° 100% 94% 12% 100%

#endif   /* end Of ADF_COLORS_H */
