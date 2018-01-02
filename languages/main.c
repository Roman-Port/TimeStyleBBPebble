#include <stdio.h>
#include <stdlib.h>


/* day names in many different languages! */
const char dayNames[37][7][8] = {
	{"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"},
	{"DIM", "LUN", "MAR", "MER", "JEU", "VEN", "SAM"},
	{"SO",  "MO",  "DI",  "MI",  "DO",  "FR",  "SA"},
	{"DOM", "LUN", "MAR", "MIÉ", "JUE", "VIE", "SÁB"},
	{"DOM", "LUN", "MAR", "MER", "GIO", "VEN", "SAB"},
	{"ZO",  "MA",  "DI",  "WO",  "DO",  "VR",  "ZA"},
	{"PAZ", "PTS", "SAL", "ÇAR", "PER", "CUM", "CTS"},
	{"NE",  "PO",  "ÚT",  "ST",  "ČT",  "PÁ",  "SO"},
	{"DOM", "SEG", "TER", "QUA", "QUI", "SEX", "SÁB"},
	{"ΚΥΡ", "ΔΕΥ", "ΤΡΙ", "ΤΕΤ", "ΠΕΜ", "ΠΑΡ", "ΣΑΒ"},
	{"SÖN", "MÅN", "TIS", "ONS", "TOR", "FRE", "LÖR"},
	{"NDZ", "PON", "WTO", "ŚRO", "CZW", "PIĄ", "SOB"},
	{"NE", "PO", "UT", "ST", "ŠT", "PI", "SO"},
	{"CN", "T2", "T3", "T4", "T5", "T6", "T7"},
	{"DUM", "LUN", "MAR", "MIE", "JOI", "VIN", "SÂM"},
	{"DG", "DL", "DT", "DC", "DJ", "DV", "DS"},
	{"SØN", "MAN", "TIR", "ONS", "TOR", "FRE", "LØR"},
	{"ВС", "ПН", "ВТ", "СР", "ЧТ", "ПТ", "СБ"},
	{"P", "E", "T", "K", "N", "R", "L"},
	{"IG", "AL", "AR", "AZ", "OG", "OL", "LR"},
	{"SU", "MA", "TI", "KE", "TO", "PE", "LA"},
	{"SØN", "MAN", "TIR", "ONS", "TOR", "FRE", "LØR"},
	{"SEK", "PIR", "ANT", "TRE", "KET", "PEN", "ŠEŠ"},
	{"NED", "PON", "TOR", "SRE", "ČET", "PET", "SOB"},
	{"VAS", "HÉT", "KED", "SZE", "CSÜ", "PÉN", "SZO"},
	{"NED", "PON", "UTO", "SRE", "ČET", "PET", "SUB"},
	{"DOM", "LUA", "MÁI", "CÉA", "DÉA", "AOI", "SAT"},
	{"SVĒ", "PIR", "OTR", "TRE", "CET", "PIE", "SES"},
	{"NE", "PO", "UT", "SR", "ČE", "PE", "SU"},
	{"日", "一", "二", "三", "四", "五", "六"},
	{"MIN", "SEN",  "SEL", "RAB", "KAM", "JUM", "SAB"},
	{"НД", "ПН", "ВТ",  "СР", "ЧТ", "ПТ", "СБ"},
	{"SUL", "LLN", "MAW", "MER", "IAU", "GWE", "SAD"},
	{"DOM", "LUN", "MAR", "MER", "XOV", "VEN", "SAB"},
	{"日", "月", "火", "水", "木", "金", "土"},
	{"일", "월", "화", "수", "목", "금", "토"},
	{"א", "ב", "ג", "ד", "ה", "ו", "ש"}
};

/* month names in many different languages! */
const char monthNames[37][12][8] = {
	{"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"},
	{"JAN", "FÉV", "MAR", "AVR", "MAI", "JUI", "JUL", "AOÛ", "SEP", "OCT", "NOV", "DÉC"},
	{"JAN", "FEB", "MÄR", "APR", "MAI", "JUN", "JUL", "AUG", "SEP", "OKT", "NOV", "DEZ"},
	{"ENE", "FEB", "MAR", "ABR", "MAY", "JUN", "JUL", "AGO", "SEP", "OCT", "NOV", "DIC"},
	{"GEN", "FEB", "MAR", "APR", "MAG", "GIU", "LUG", "AGO", "SET", "OTT", "NOV", "DIC"},
	{"JAN", "FEB", "MRT", "APR", "MEI", "JUN", "JUL", "AUG", "SEP", "OKT", "NOV", "DEC"},
	{"OCA", "ŞUB", "MAR", "NİS", "MAY", "HAZ", "TEM", "AĞU", "EYL", "EKİ", "KAS", "ARA"},
	{"LED", "ÚNO", "BŘE", "DUB", "KVĚ", "ČRV", "ČVC", "SRP", "ZÁŘ", "ŘÍJ", "LIS", "PRO"},
	{"JAN", "FEV", "MAR", "ABR", "MAI", "JUN", "JUL", "AGO", "SET", "OUT", "NOV", "DEZ"},
	{"ΙΑΝ", "ΦΕΒ", "ΜΑΡ", "ΑΠΡ", "ΜΑΪ", "ΙΟΝ", "ΙΟΛ", "ΑΥΓ", "ΣΕΠ", "ΟΚΤ", "ΝΟΕ", "ΔΕΚ"},
	{"JAN", "FEB", "MAR", "APR", "MAJ", "JUN", "JUL", "AUG", "SEP", "OKT", "NOV", "DEC"},
	{"STY", "LUT", "MAR", "KWI", "MAJ", "CZE", "LIP", "SIE", "WRZ", "PAŹ", "LIS", "GRU"},
	{"JAN", "FEB", "MAR", "APR", "MÁJ", "JÚN", "JÚL", "AUG", "SEP", "OKT", "NOV", "DEC"},
	{"Th1", "Th2", "Th3", "Th4", "Th5", "Th6", "Th7", "Th8", "Th9", "T10", "T11", "T12"},
	{"IAN", "FEB", "MAR", "APR", "MAI", "IUN", "IUL", "AUG", "SEP", "OCT", "NOI", "DEC"},
	{"GEN", "FEB", "MAR", "ABR", "MAI", "JUN", "JUL", "AGO", "SET", "OCT", "NOV", "DES"},
	{"JAN", "FEB", "MAR", "APR", "MAI", "JUN", "JUL", "AUG", "SEP", "OKT", "NOV", "DES"},
	{"ЯНВ", "ФЕВ", "МАР", "АПР", "МАЙ", "ИЮН", "ИЮЛ", "АВГ", "СЕН", "ОКТ", "НОЯ", "ДЕК"},
	{"JAN", "VEB", "MÄR", "APR", "MAI", "JUN", "JUL", "AUG", "SEP", "OKT", "NOV", "DET"},
	{"URT", "OTS", "MAR", "API", "MAI", "EKA", "UZT", "ABU", "IRA", "URR", "AZA", "ABE"},
	{"TAM", "HEL", "MAA", "HUH", "TOU", "KES", "HEI", "ELO", "SYY", "LOK", "MAR", "JOU"},
	{"JAN", "FEB", "MAR", "APR", "MAJ", "JUN", "JUL", "AUG", "SEP", "OKT", "NOV", "DEC"},
	{"SAU", "VAS", "KOV", "BAL", "GEG", "BIR", "LIE", "RUG", "RGS", "SPA", "LAP", "GRU"},
	{"JAN", "FEB", "MAR", "APR", "MAJ", "JUN", "JUL", "AVG", "SEP", "OKT", "NOV", "DEC"},
	{"JAN", "FEB", "MÁR", "ÁPR", "MÁJ", "JÚN", "JÚL", "AUG", "SZE", "OKT", "NOV", "DEC"},
	{"SIJ", "VEL", "OŽU", "TRA", "SVI", "LIP", "SRP", "KOL", "RUJ", "LIS", "STU", "PRO"},
	{"EAN", "FEA", "MÁR", "AIB", "BEA", "MEI", "IÚI", "LÚN", "MFÓ", "DFÓ", "SAM", "NOL"},
	{"JAN", "FEB", "MAR", "APR", "MAI", "JŪN", "JŪL", "AUG", "SEP", "OKT", "NOV", "DEC"},
	{"JAN", "FEB", "MAR", "APR", "MAJ", "JUN", "JUL", "AVG", "SEP", "OKT", "NOV", "DEC"},
	{"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"},
	{"JAN", "FEB", "MAR", "APR", "MEI", "JUN", "JUL", "AGU", "SEP", "OKT", "NOV", "DES"},
	{"СІЧ", "ЛЮТ", "БЕР", "КВІ", "ТРА", "ЧЕР", "ЛИП", "СЕР", "ВЕР", "ЖОВ", "ЛИС", "ГРУ"},
	{"ION", "CHW", "MAW", "EBR", "MAI", "MEH", "GOR", "AWS", "MED", "HYD", "TCH", "RHA"},
	{"XAN", "FEB", "MAR", "ABR", "MAI", "XUÑ", "XUL", "AGO", "SET", "OUT", "NOV", "NAD"},
	{"1月", "2月", "3月", "4月", "5月", "6月", "7月", "8月", "9月", "10月", "11月", "12月"},
	{"1월", "2월", "3월", "4월", "5월", "6월", "7월", "8월", "9월", "10월", "11월", "12월"},
	{"ינו", "פבר", "מרץ", "אפר", "מאי", "יונ", "יול", "אוג", "ספט", "אוק", "נוב", "דצמ"}
};

// all of these are taken from:
// http://www.unicode.org/cldr/charts/28/by_type/date_&_time.fields.html#521165cf49647551
const char wordForWeek[37][12] = {
	"Wk",
	"Sem",
	"W",
	"Sem",
	"Sett",
	"Wk",
	"Hf",
	"Týd",
	"Sem",
	"εβδ",
	"V",
	"Tydz",
	"Týž",
	"Tuần",
	"Săpt",
	"Setm",
	"Uke",
	"нед",
	"Näd",
	"Ast",
	"Vk",
	"Uge",
	"Sav",
	"Ted",
	"Hét",
	"Tj",
	"Scht",
	"Ned",
	"Ned",
	"周",
	"Ming",
	"Тиж",
	"Wnos",
	"Sem",
	"週",
	"주",
	"שב"
};

#define ARRAY_SIZE (7 * 8)

int main(void)
{
  FILE *fp;
  char testarray[7][8];

  int i;

  if((fp=fopen("test", "wb"))==NULL) {
    printf("Cannot open file.\n");
  }


  if(fwrite(dayNames[0], sizeof(char), ARRAY_SIZE, fp) != ARRAY_SIZE)
    printf("File read error.");
  fclose(fp);

  /* read the values */
  if((fp=fopen("test", "rb"))==NULL) {
    printf("Cannot open file.\n");
  }

  if(fread(testarray, sizeof(char), ARRAY_SIZE, fp) != ARRAY_SIZE) {
    if(feof(fp))
       printf("Premature end of file.");
    else
       printf("File read error.");
  }
  fclose(fp);

  for(i=0; i<7; i++)
    printf("%s ", testarray[i]);

  return 0;
}
