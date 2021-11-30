;	a,b,c – współczynniki funkcji kwadratowej
;	delta – wartość trójmianu kwadratowego funkcji kwadratowej
;	pierwiastek – pierwiastek kwadratowy z trójmianu
;	x1,x2 – miejsca zerowe funkcji kwadratowej



	
	_TEXT  SEGMENT
	count_deltaroot  PROC
	    
	    xorpd xmm3, xmm3 ; Zerowanie rejestru XMM3
	    movapd xmm3, xmm0 ; Skopiowanie wartości delta do XMM3
	    xorpd xmm0, xmm0 ; Zerowanie rejestru XMM0
	    sqrtpd xmm0, xmm3 ; Zapisanie pierwiastka z delta do XMM0
	    ret
	
	count_deltaroot ENDP
	    
	
	count_delta PROC
	
	    xorpd xmm3, xmm3 ; Zerowanie rejestru XMM3
	    movapd xmm3, xmm1 ; Skopiowanie wartości b do XMM3
	    mulpd xmm3, xmm1 ; Pomnożenie b*b
	    mulpd xmm2, xmm0 ; Pomnożenie a*c
	    addpd xmm2, xmm2 ; Pomnożenie ac*2
	    addpd xmm2, xmm2 ; Pomnożenie ac*2*2 (aby otrzymać 4ac)
	    xorpd xmm0, xmm0 ; Zerowanie rejestru XMM0
	    movapd xmm0, xmm3 ; Skopiowanie b*b do XMM0
	    subpd xmm0, xmm2 ; Odjęcie 4ac od b*b
	    ret
	
	count_delta ENDP
	
	
	count_p PROC
	
	    xorpd xmm2, xmm2 ; Zerowanie rejestru XMM2
	    movapd xmm2, xmm0 ; Skopiowanie wartości a do XMM2
	    addpd xmm2, xmm2 ; Pomnożenie a*2
	    xorpd xmm0, xmm0 ; Zerowanie rejestru XMM0
	    subpd xmm0, xmm1 ; Umieszczenie w rejestrze XMM0 wartości -b
	    divpd xmm0, xmm2 ; Podzielenie -b/2a
	    ret
	
	count_p ENDP
	

	count_q PROC
	
	    xorpd xmm2, xmm2 ; Zerowanie rejestru XMM2
	    movapd xmm2, xmm0 ; Skopiowanie wartości a do XMM2
	    addpd xmm2, xmm2 ; Pomnożenie a*2
	    addpd xmm2, xmm2 ; Pomnożenie a*2*2
	    xorpd xmm0, xmm0 ; Zerowanie rejestru XMM0
	    subpd xmm0, xmm1 ; Umieszczenie w rejestrze XMM0 wartości -delta
	    divpd xmm0, xmm2 ; Podzielenie -delta/4a
	    ret
	
	count_q ENDP
	
	
	count_x1 PROC
	
	    xorpd xmm3, xmm3 ; Zerowanie rejestru XMM3
	    movapd xmm3, xmm0 ; Skopiowanie wartości a do XMM3
	    addpd xmm3, xmm3 ; Pomnożenie a*2
	    xorpd xmm0, xmm0 ; Zerowanie rejestru XMM0
	    subpd xmm0, xmm1 ; Umieszczenie w rejestrze XMM0 wartości -b
	    subpd xmm0, xmm2 ; Odjęcie od rejestru XMM0 wartości pierwiastek
	    divpd xmm0, xmm3 ; Podzielenie (-b-pierwiastek)/2a
	    ret
	
	count_x1 ENDP
	
	
	count_x2 PROC
	
	    xorpd xmm3, xmm3 ; Zerowanie rejestru XMM3
	    movapd xmm3, xmm0 ; Skopiowanie wartości a do XMM3
	    addpd xmm3, xmm3 ; Pomnożenie a*2
	    xorpd xmm0, xmm0 ; Zerowanie rejestru XMM0
	    subpd xmm0, xmm1 ; Umieszczenie w rejestrze XMM0 wartości -b
	    addpd xmm0, xmm2 ; Dodanie do rejestru XMM0 wartości pierwiastek
	    divpd xmm0, xmm3 ; Podzielenie (-b+pierwiastek)/2a
	    ret
	
	count_x2 ENDP
	
	
	_TEXT  ENDS
	
	
 END          ; END directive required at end of file
