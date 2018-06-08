	AREA Signal, DATA, READONLY
	export TabSig
; fonction cosinus, frequence relative 1, phase -90 degres, amplitude max
; valeurs attendues pour k = 1 :
;	Re	0xFFFFF800	env 0
;	Im	0x7FFFD135	env +2^31
;	M2	0x3FFFD135	env 2^30
; pour 1 > k > 63
;	M2    < 0x0000000F

TabSig
	dcw	0x0800	;  0   2048  0.50000
	dcw	0x08c9	;  1   2249  0.54907
	dcw	0x0990	;  2   2448  0.59766
	dcw	0x0a53	;  3   2643  0.64526
	dcw	0x0b10	;  4   2832  0.69141
	dcw	0x0bc5	;  5   3013  0.73560
	dcw	0x0c72	;  6   3186  0.77783
	dcw	0x0d13	;  7   3347  0.81714
	dcw	0x0da8	;  8   3496  0.85352
	dcw	0x0e2f	;  9   3631  0.88647
	dcw	0x0ea7	; 10   3751  0.91577
	dcw	0x0f0e	; 11   3854  0.94092
	dcw	0x0f64	; 12   3940  0.96191
	dcw	0x0fa8	; 13   4008  0.97852
	dcw	0x0fd9	; 14   4057  0.99048
	dcw	0x0ff6	; 15   4086  0.99756
	dcw	0x0fff	; 16   4095  0.99976
	dcw	0x0ff6	; 17   4086  0.99756
	dcw	0x0fd9	; 18   4057  0.99048
	dcw	0x0fa8	; 19   4008  0.97852
	dcw	0x0f64	; 20   3940  0.96191
	dcw	0x0f0e	; 21   3854  0.94092
	dcw	0x0ea7	; 22   3751  0.91577
	dcw	0x0e2f	; 23   3631  0.88647
	dcw	0x0da8	; 24   3496  0.85352
	dcw	0x0d13	; 25   3347  0.81714
	dcw	0x0c72	; 26   3186  0.77783
	dcw	0x0bc5	; 27   3013  0.73560
	dcw	0x0b10	; 28   2832  0.69141
	dcw	0x0a53	; 29   2643  0.64526
	dcw	0x0990	; 30   2448  0.59766
	dcw	0x08c9	; 31   2249  0.54907
	dcw	0x0800	; 32   2048  0.50000
	dcw	0x0737	; 33   1847  0.45093
	dcw	0x0670	; 34   1648  0.40234
	dcw	0x05ad	; 35   1453  0.35474
	dcw	0x04f0	; 36   1264  0.30859
	dcw	0x043b	; 37   1083  0.26440
	dcw	0x038e	; 38    910  0.22217
	dcw	0x02ed	; 39    749  0.18286
	dcw	0x0258	; 40    600  0.14648
	dcw	0x01d1	; 41    465  0.11353
	dcw	0x0159	; 42    345  0.08423
	dcw	0x00f2	; 43    242  0.05908
	dcw	0x009c	; 44    156  0.03809
	dcw	0x0058	; 45     88  0.02148
	dcw	0x0027	; 46     39  0.00952
	dcw	0x000a	; 47     10  0.00244
	dcw	0x0000	; 48      0  0.00000
	dcw	0x000a	; 49     10  0.00244
	dcw	0x0027	; 50     39  0.00952
	dcw	0x0058	; 51     88  0.02148
	dcw	0x009c	; 52    156  0.03809
	dcw	0x00f2	; 53    242  0.05908
	dcw	0x0159	; 54    345  0.08423
	dcw	0x01d1	; 55    465  0.11353
	dcw	0x0258	; 56    600  0.14648
	dcw	0x02ed	; 57    749  0.18286
	dcw	0x038e	; 58    910  0.22217
	dcw	0x043b	; 59   1083  0.26440
	dcw	0x04f0	; 60   1264  0.30859
	dcw	0x05ad	; 61   1453  0.35474
	dcw	0x0670	; 62   1648  0.40234
	dcw	0x0737	; 63   1847  0.45093
	end