typedef union{
  char* y_str;
  int y_int;
  double y_dbl;
  bool y_boo;
  int y_col[3];
} YYSTYPE;
#define	INTEGER	258
#define	NUMBER	259
#define	STRING	260
#define	LBRACE	261
#define	RBRACE	262
#define	LPARE	263
#define	RPARE	264
#define	COMMA	265
#define	CAT	266
#define	ASSIGN	267
#define	SOURCE	268
#define	PLURAL	269
#define	RACE	270
#define	PLANET	271
#define	OWNER	272
#define	ORIGINAL_STATS	273
#define	STATS	274
#define	MINERAL_CONC	275
#define	MINERALS	276
#define	POPULATION	277
#define	INSTALLATIONS	278
#define	POSITION	279
#define	RT	280
#define	HIMMUNE	281
#define	DEFCOVERAGE	282
#define	HABITABILITY	283
#define	COL_RES	284
#define	GROWTH	285
#define	FACTORIES	286
#define	MINES	287
#define	TECH_COST	288
#define	TECH	289
#define	MIN_POP_MOVE	290
#define	MINE_YEARS	291
#define	HOMEWORLD	292
#define	ALLIANCE	293
#define	SCAN	294
#define	AUTOBUILD	295
#define	QUEUE	296
#define	CLONE	297
#define	DOLLAR	298
#define	SIMFUTURE	299
#define	MAXZOOM	300
#define	STARSID	301
#define	UNIVERSE	302
#define	YEAR	303
#define	WFUNCTION	304
#define	RELIABILITY	305
#define	PERCENT	306
#define	STARBASE	307
#define	REPORTAGE	308
#define	ANALYZE	309
#define	PNEWCOLONY	310
#define	PBREEDER	311
#define	PPRODUCTION	312
#define	PLOOT	313
#define	PGENERIC	314
#define	PMINING	315
#define	SHIPS	316
#define	FLEET	317
#define	FUEL	318
#define	CARGO	319
#define	DESTINATION	320
#define	OBJECT	321
#define	RESOURCES	322
#define	WAYPOINTTASK	323
#define	STARSETA	324
#define	BATTLEPLAN	325
#define	WARP	326
#define	MINELAYSWEEP	327
#define	CLOAKING	328
#define	TFORMING	329
#define	PLANETVIEW	330
#define	ROUTING	331
#define	COMPOSITION	332
#define	FLEETVIEW	333
#define	COLOR	334
#define	MAXPIERADIUS	335
#define	PLUS	336
#define	MINUS	337
#define	MULTIPLY	338
#define	DIVIDE	339
#define	RAISE	340
#define	UMINUS	341


extern YYSTYPE yylval;
