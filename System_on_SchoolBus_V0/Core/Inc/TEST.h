struct THONGTIN
{
    uint8_t ID[5];
    char Ho_Ten[30];
    char Lop[5];
    char SDT[11];  
    uint8_t state;
    uint8_t hour;
    uint8_t minute;  
};
struct THONGTIN HOCSINH[10];

void kt()
{
    strcpy(HOCSINH[0].Ho_Ten,"Nguyen Van A");
    strcpy(HOCSINH[0].Lop,"10A8");
    strcpy(HOCSINH[0].SDT,"1234567890");
    HOCSINH[0].ID[0]=0x1a;
    HOCSINH[0].ID[1]=0x24;
    HOCSINH[0].ID[2]=0x1e;
    HOCSINH[0].ID[3]=0x40;
    HOCSINH[0].ID[4]=0x60;

    //HOC SINH 1
    strcpy(HOCSINH[1].Ho_Ten,"Tran Van B");
    strcpy(HOCSINH[1].Lop,"11A9");
    strcpy(HOCSINH[1].SDT,"0120340560");
    HOCSINH[1].ID[0]=0xca;
    HOCSINH[1].ID[1]=0x6d;
    HOCSINH[1].ID[2]=0x51;
    HOCSINH[1].ID[3]=0xb4;
    HOCSINH[1].ID[4]=0x42;

    //HOC SINH 2
    strcpy(HOCSINH[2].Ho_Ten,"Dinh Van C");
    strcpy(HOCSINH[2].Lop,"7a2");
    strcpy(HOCSINH[2].SDT,"9876005432");
    HOCSINH[2].ID[0]=0xf1;
    HOCSINH[2].ID[1]=0xb2;
    HOCSINH[2].ID[2]=0xa9;
    HOCSINH[2].ID[3]=0xc1;
    HOCSINH[2].ID[4]=0x12;
    
    //HOC SINH 3
    strcpy(HOCSINH[3].Ho_Ten,"TRAN LONG HAI");
    strcpy(HOCSINH[3].Lop,"DD18");
    strcpy(HOCSINH[3].SDT,"9876005432");
    HOCSINH[3].ID[0]=0x99;
    HOCSINH[3].ID[1]=0xef;
    HOCSINH[3].ID[2]=0x4b;
    HOCSINH[3].ID[3]=0xb3;
    HOCSINH[3].ID[4]=0x8e;
}
