
#include <stdio.h>
#include <stdlib.h>
int gcd(int e, int L){
	int mod;
	if((e == 0)||(L == 0))
	return(0);
	while(1){
		mod = L % e;
		if(mod == 0)
		break;
		L = e;
		e = mod;
	}
		return(e);
}

int gcde (int L){
	int e,result;
	for (e = 2; e < L; e++){
		if (gcd(e,L) == 1){
			result = e;
			break;
		}
	}
return(result);
}
 
int decide(int kaisi){
	int L,e;
 	int a;
 	int b;     
	int x0,x1,x2;
 	int y0,y1,y2;
 	int z0,z1,z2;
 	int p,q,r;
 	int i,j;
 	int n;
 	printf("素数p,qを決めてください \n");
 	printf("p : "); scanf("%d", &p);
 	printf("q : "); scanf("%d", &q);
 	L = ((p-1) * (q-1))/gcd((p-1),(q-1));
 	e = gcde(L);
 	n = p * q;
 	if(kaisi == 1){
		printf("公開鍵を表示します \n");
   		printf("e,n=%d,%d \n",e,n);
 	}
	z0=L;
 	z1=e;
 	x0=1;
 	x1=0;
 	y0=0;
 	y1=1;
 	while(z1!=0){
   		z2 = z0%z1;
   		q = (z0 - z2)/z1;
   		x2 = x0 - q*x1;
   		y2 = y0 - q*y1;
		if(z2 == 0){
			if(kaisi == 2){
				printf("秘密鍵の表示します \n");
				printf("d_e,n=%d,%d \n",y1,n);
			}
			return(n);
			}
		x0=x1;
   		x1=x2;
   		y0=y1;
   		y1=y2;
   		z0=z1;
   		z1=z2;
 	}
	return 0;
}

int conversion(int n, int cter, int key){
	int i;
	int ex_cter;
 	ex_cter = cter;
 	for(i = 1; i != key; i++){
		cter = (cter * ex_cter) % n;
 	}
 	return(cter);
}

int cipher(int n){
	FILE  *fpr, *fpw;
 	int little = 256;
 	int L0,L1;
 	int pubkey;
 	int cter;
 	char namer[100], namew[100];
 	printf("暗号化するファイル名を入力してください : "); scanf("%s",namer);
 	printf("出力するファイル名を入力してください : "); scanf("%s",namew);
 	printf("表示されている公開鍵の入力してください : "); 
	scanf("%d",&pubkey);
	if((fpr=fopen(namer,"r")) == NULL)
	exit(1);
	if((fpw=fopen(namew,"w")) == NULL)
	exit(1);
	while((cter=fgetc(fpr)) != EOF){
   		cter = conversion(n,cter,pubkey);
   		L0 = cter % little;
   		L1 = (cter -L0)/little;
   		fputc(L0,fpw);
   		fputc(L1,fpw);
	}
	fclose(fpr);
	fclose(fpw);
	return 0;
}

int complex(int n){
	FILE  *fpr, *fpw;
 	int little = 256;
 	int L0,L1;
 	int seckey;
 	int cter,result;
 	char namer[20], namew[20];
 	printf("復号化するファイル名を入力してください : "); scanf("%s",namer);
 	printf("出力するファイル名を入力してください : "); scanf("%s",namew);
 	printf("表示されている秘密鍵を入力を入力してください: "); scanf("%d",&seckey);
 	if((fpr=fopen(namer,"r")) == NULL)
   	exit(1);
	if((fpw=fopen(namew,"w")) == NULL)
   	exit(1);
	while((cter=fgetc(fpr)) != EOF){
   		L0 = cter;
   		L1 = fgetc(fpr);
   		cter = (L1 * little) + L0;
   		cter = conversion(n,cter,seckey);
   		fputc(cter,fpw);
	}
	fclose(fpr);
	fclose(fpw);
	return 0;
}
int main(void){
 	int kaisi;
 	int n;
	start:
 	printf("暗号化する場合:1,復号化する場合:2を選択してください");
 	scanf("%d",&kaisi);
 	if(kaisi == 1){
   		n = decide(kaisi);
   		cipher(n);
 	}
	else if(kaisi == 2){
		n = decide(kaisi);
   		complex(n);
	}
	else{
		goto start;
	}
}
/*	使ったもの（参考にしたもの）
	中国人剰余定理
	ラビン暗号
	エルガマル暗号
	ユークリッドの互除算
	拡張ユークリッドの互除算
	最大公約数と最小公倍数の関係
	B進展開
	バイナリファイル
	エディアン
	
	先生からのコメント
	素数の型がintなので簡単に破られる
	pqがわかると全部わかってしまうのはおかしい*/