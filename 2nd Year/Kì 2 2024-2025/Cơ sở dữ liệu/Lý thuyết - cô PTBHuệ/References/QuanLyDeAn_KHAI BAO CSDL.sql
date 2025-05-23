create database QuanLyDeAn

Create	table NHANVIEN
(
	HONV	nvarchar(15),
	TENLOT	nvarchar(15),
	TENNV	nvarchar(15) not null,
	MANV	char	(9) not null,
	NGSINH	Datetime,
	DCHI	nvarchar(30),
	PHAI	nvarchar(3),
	LUONG	float,
	MA_NQL	char(9),
	PHG	int,
	constraint PK_NHANVIEN primary key(MANV),
	
)
drop table nhanvien

Create	table PHONGBAN
(
	TENPHG	nvarchar(15),
	MAPHG	int not null,
	TRPHG	char(9),
	NG_NHANCHUC Datetime
	constraint PK_PHONGBAN primary key(MAPHG)
)


Create table DIADIEM_PHG
(
	MAPHG	int,
	DIADIEM nvarchar(50)
	constraint PK_DIADIEM_PHG primary key (MAPHG, DIADIEM)
)

Create table DEAN
(
	TENDA	nvarchar(15),
	MADA	int,
	DDIEM_DA nvarchar(50),
	PHONG	int,
	constraint PK_DEAN primary key(MADA)
)

Create table PHANCONG
(
	MA_NVIEN char(9),
	MADA	 int,
	THOIGIAN float,
	constraint PK_PHANCONG primary key (MA_NVIEN, MADA)
)

Create	table THANNHAN
(
	MA_NVIEN char(9),
	TENTN	 nvarchar(15),
	PHAI	 nvarchar(3),
	NGSINH	Datetime,
	QUANHE 	nvarchar(15),
	constraint PK_THANNHAN primary key (MA_NVIEN, TENTN) 
)

----------------------------------*tao khoa ngoai*---------------------------
--tao khoa ngoai cho bang NHANVIEN
alter table NHANVIEN
add 
constraint FK_NHANVIEN_NHANVIEN foreign key(MA_NQL) references NHANVIEN(MANV),
constraint FK_NHANVIEN_PHONGBAN foreign key(PHG) references PHONGBAN(MAPHG)
--tao khoa ngoai cho bang PHONGBAN
sp_help NHANVIEN
alter table NHANVIEN drop constraint FK_NHANVIEN_PHONGBAN
alter table NHANVIEN add
constraint FK_NHANVIEN_PHONGBAN foreign key(PHG) references PHONGBAN(MAPHG)
alter table PHONGBAN
add
constraint FK_PHONGBAN_NHANVIEN foreign key(TRPHG) references NHANVIEN(MANV)
--tao khoa ngoai cho bang DIADIEM_PHG
alter table DIADIEM_PHG
add
constraint FK_DIADIEMPHG_PHONGBAN foreign key(MAPHG) references PHONGBAN(MAPHG)
--tao khoa ngoai cho bang DEAN
alter table DEAN
add
constraint FK_DEAN_PHONGBAN foreign key(PHONG) references PHONGBAN(MAPHG)

alter table PHANCONG
add
constraint FK_PHANCONG_DEAN foreign key(MADA) references DEAN(MADA),
constraint FK_PHANCONG_NHANVIEN foreign key(MA_NVIEN) references NHANVIEN(MANV)

alter table THANNHAN
add constraint FK_THANNHAN_NHANVIEN foreign key(MA_NVIEN) references NHANVIEN(MANV)

--------------------------Chen du lieu -------------------------------------------
set dateformat dmy

select * from NHANVIEN
DELETE NHANVIEN WHERE MANV = '011'  

UPDATE NHANVIEN
SET LUONG = 25000
WHERE MANV = '010'

SELECT *
FROM NHANVIEN 
WHERE PHAI = 'Nam'

SELECT manv, honv, tenlot, tennv, luong
FROM NHANVIEN 

SELECT manv, honv, tenlot, tennv, luong
FROM NHANVIEN 
WHERE PHAI = 'Nam'





insert into NHANVIEN values(N'Vương', N'Ngọc', N'Quyền', 
'006', '01/01/1965', N'45 Trưng Vương Hà Nội', N'Nữ', 55000, null, null)

insert into NHANVIEN values(N'Nguyễn', N'Thanh', N'Tùng', 
'005', '20/08/1962', N'222 Nguyễn Văn Cừ TPHCM', N'Nam', 40000, NULL, null) /*006*/

insert into NHANVIEN values(N'Lê', N'Thị', N'Nhàn', 
'001', '01/02/1967', N'291 Hồ Văn Huê TPHCM', N'Nữ', 43000, NULL, null)/*006*/

insert into NHANVIEN values(N'Nguyễn', N'Mạnh', N'Hùng', 
'004', '04/03/1967', N'95 Bà Rịa Vũng Tàu', N'Nam', 38000, NULL, null)/*005*/

insert into NHANVIEN values(N'Trần', N'Thanh', N'Tâm', 
'003', '04/05/1957', N'34 Mai Thị Lựu TPHCM', N'Nam', 25000, NULL, null) /*005*/

insert into NHANVIEN values(N'Bùi', N'Thúy', N'Bư', 
'007', '11/03/1954', N'332 Nguyễn Thái Học TPHCM', N'Nam', 25000, NULL, null)/*001*/

insert into NHANVIEN values(N'Trần', N'Hồng', N'Quang', 
'008', '01/09/1967', N'80 Lê Hồng Phong TPHCM', N'Nam', 25000, NULL, null) /*001*/

insert into NHANVIEN values(N'Đinh', N'Bá', N'Tiến', 
'009', '12/01/1960', N'119 Cống Quỳnh TPHCM', N'Nam', 30000, NULL, null) /*005*/

select *
from NHANVIEN

Select *
from PHONGBAN

-- nhap du lieu cho PHONGBAN

insert into PHONGBAN values(N'Nghiên Cứu', 5, '005', '22/05/1987')
insert into PHONGBAN values(N'Diều Hành', 4, '008', '01/01/1985')
insert into PHONGBAN values(N'Quản Lý', 1, '006', '19/06/1971')
insert into PHONGBAN values(N'Tổng hợp', 2,'005', '19/06/1971')
SELECT * FROM PHONGBAN
--cap nhat lai du lieu PHONG cho nhan vien

update NHANVIEN
set    PHG = 5
where  MANV = '009'

update NHANVIEN
set    PHG = 5
where  MANV = '005'

update NHANVIEN
set    PHG = 4
where  MANV = '007'

update NHANVIEN
set    PHG = 4
where  MANV = '001'

update NHANVIEN
set    PHG = 5
where  MANV = '003'

update NHANVIEN
set    PHG = 5
where  MANV = '004'

update NHANVIEN
set    PHG = 4
where  MANV = '008'

update NHANVIEN
set    PHG = 1
where  MANV = '006'

update NHANVIEN
set    PHG = 5
where  MANV = '009'

select *
from NHANVIEN

--cap nhat du lieu cho bang DIADIEM_PHG

insert into DIADIEM_PHG values(1, 'TP HCM')
insert into DIADIEM_PHG values(4, 'HA NOI')
insert into DIADIEM_PHG values(5, 'VUNG TAU')

select *
from DIADIEM_PHG

--cap nhat du lieu cho bang DEAN
insert into DEAN values(N'Sản phẩm X', 1, 'VUNG TAU', 5)
insert into DEAN values(N'Sản phẩm Y', 2, 'NHA TRANG', 5)
insert into DEAN values(N'Sản phẩm Z', 3, 'TP HCM', 5)
insert into DEAN values(N'Tin học hóa', 10, 'HA NOI', 4)
insert into DEAN values(N'Cap Quang', 20, 'TP HCM', 1)
insert into DEAN values(N'Đào Tạo', 30, 'HA NOI', 4)
insert into DEAN values(N'NL CLC', 40, 'HA NOI', 5)

select *
from DEAN
SELECT * FROM THANNHAN
--cap nhat du lieu cho bang THANNHAN
insert into THANNHAN values('005', N'Quang', N'Nữ', '05/04/1976', N'Con gái')
insert into THANNHAN values('005', N'Khang', N'Nam', '25/10/1973', N'Con trai')
insert into THANNHAN values('005', N'Dương', N'Nữ', '03/05/1948', N'Vợ chồng')
insert into THANNHAN values('001', N'Đăng', N'Nam', '19/02/1932', N'Vợ chồng')
insert into THANNHAN values('009', N'Duy', N'Nam', '01/01/1978', N'Con trai')
insert into THANNHAN values('009', N'Châu', N'Nữ', '30/12/1978', N'Con gái')
insert into THANNHAN values('009', N'Phương', N'Nữ', '05/05/1957', N'Vợ chồng')

select *
from THANNHAN

--chen du lieu cho bang PHANCONG
insert into PHANCONG values('009', 1, 32)
insert into PHANCONG values('009', 2, 8)
insert into PHANCONG values('004', 3, 40)
insert into PHANCONG values('003', 1, 20)
insert into PHANCONG values('003', 2, 20)
insert into PHANCONG values('008', 10,35)
insert into PHANCONG values('008', 30,5)
insert into PHANCONG values('001', 30,20)
insert into PHANCONG values('001', 20,15)
insert into PHANCONG values('006', 20,30)
insert into PHANCONG values('005', 3, 10)
insert into PHANCONG values('005', 10,10)
insert into PHANCONG values('005', 20,10)
insert into PHANCONG values('007', 30,30)
insert into PHANCONG values('007', 10,10)

select *
from	PHANCONG


set dateformat myd
sp_help nhanvien



--===================###CAC CAU TRUY VAN###===========================
--Cac cau truy van don gian
--1--Tim nhung nhan vien lam viec o phong so 4

select NV.MANV, NV.HONV, NV.TENLOT, NV.TENNV
from NHANVIEN NV
where PHG = 4

--2--Tim nhung nhan vien co muc luong ten 30000

select NV.MANV, NV.HOVN, NV.TENLOT, NV.TENNV, NV.LUONG, NV.PHG
from NHANVIEN NV
where NV.LUONG > 30000

--3--
	/*
	Tim cac nhan vien co muc luong tren 25000 o PHG = 4 hay
	cac nhan vien co muc luong tren 30000 o PHG = 5
	*/

select NV.MANV, NV.HONV, NV.TENLOT, NV.TENNV, NV.LUONG, NV.PHG
from NHANVIEN NV
where NV.LUONG > 25000 and PHG = 4 or NV.LUONG > 30000 and PHG = 5

--4--cho biet ho ten day du cua cac nhan vien o TPHCM

select NV.MANV, NV.HONV, NV.TENLOT, NV.TENNV
from NHANVIEN NV, DIADIEM_PHG
where NV.PHG = DIADIEM_PHG.MAPHG and DIADIEM_PHG.DIADIEM = 'TP HCM'

select *
from NHANVIEN


--5--cho biet ngay sinh va dia chi cua nhan vien DInh Ba Tien


Select *
from nhanvien
where phai = N'NỮ' OR PHG = 5

Select *
from nhanvien
where PHG = 5 and LUONG >=30000

Select distinct PHG
from nhanvien

SELECT MANV, HONV + ' ' + TENLOT + ' '+ TEN
FROM NHANVIEN
where PHG = 5

SELECT MANV, MADA
FROM NHANVIEN, DEAN

SELECT MADA
FROM DEAN

SELECT MANV, HONV, TENLOT, TEN, PHG, TENPHG
FROM NHANVIEN, PHONGBAN
WHERE PHG = MAPHG

SELECT MANV, HONV, TENLOT, TEN, PHG, TENPHG
FROM NHANVIEN INNER JOIN PHONGBAN
ON PHG = MAPHG

SELECT NV1.MANV, NV1.HONV, NV1.TENLOT, NV1.TEN, NV2.TEN
FROM NHANVIEN NV1,NHANVIEN NV2
WHERE NV1.MA_NQL = NV2.MANV


Select * 
From NHANVien

SELECT DISTINCT LUONG
FROM NHANVIEN


SELECT MANV, TENNV, PHG, MAPHG,TENPHG
FROM NHANVIEN nv, PHONGBAN pb
WHERE nv.PHG = pb.MAPHG

SELECT NV1.MANV, NV1.HONV, NV1.TENLOT, NV1.TENNV, NV1.MA_NQL AS MANQL, NV2.HONV AS HONQL, NV2.TENLOT TENLOTNQL, NV2.TENNV TENNQL
FROM NHANVIEN NV1, NHANVIEN NV2
WHERE NV1.MA_NQL = NV2.MANV


SELECT NV1.MANV, NV1.HONV + ' ' + NV1.TENLOT + ' ' + NV1.TENNV AS [Nhan Vien],
                 NV2.HONV + ' ' + NV2.TENLOT + ' ' + NV2.TENNV AS [Nguoi Quan Ly]
FROM NHANVIEN NV1, NHANVIEN NV2
WHERE NV1.MA_NQL = NV2.MANV


SELECT MANV, HONV, TENLOT, TENNV, PHG, TENPHG
FROM NHANVIEN LEFT JOIN PHONGBAN
ON PHG = MAPHG

SELECT MA_NVIEN, DEAN.MADA, TENDA
FROM PHANCONG RIGHT JOIN DEAN
ON PHANCONG.MADA = DEAN.MADA

SELECT MANV, TENNV, PHG, MAPHG,TENPHG
FROM NHANVIEN, PHONGBAN
WHERE PHG = MAPHG

SELECT MANV, HONV, TENLOT, TENNV, PHG, TENPHG
FROM NHANVIEN inner JOIN PHONGBAN
ON PHG = MAPHG

SELECT MANV, HONV, TENLOT, TENNV, PHG
FROM NHANVIEN where phg in (select maphg from PHONGBAN)

SELECT MA_NVIEN
FROM PHANCONG
WHERE MADA = 10
UNION
SELECT MA_NVIEN
FROM PHANCONG
WHERE MADA = 30

SELECT DISTINCT MA_NVIEN
FROM PHANCONG
WHERE MADA = 10 OR MADA = 30

SELECT MA_NVIEN
FROM PHANCONG
WHERE MADA = 10
INTERSECT
SELECT MA_NVIEN
FROM PHANCONG
WHERE MADA = 30

SELECT MA_NVIEN
FROM PHANCONG
WHERE MADA = 10 AND MA_NVIEN NOT IN (SELECT MA_NVIEN
FROM PHANCONG
WHERE MADA = 30)

SELECT MA_NVIEN
FROM PHANCONG
WHERE MADA = 30


SELECT *
FROM NHANVIEN INNER JOIN PHONGBAN ON PHG = MAPHG

SELECT *
FROM NHANVIEN LEFT JOIN PHONGBAN ON PHG = MAPHG

SELECT *
FROM NHANVIEN RIGHT JOIN PHONGBAN ON PHG = MAPHG

SELECT *
FROM NHANVIEN FULL OUTER JOIN PHONGBAN ON PHG = MAPHG

Select MANV, MADA, 10
from DEAN, NHANVIEN

SELECT * FROM PHANCONG_1

Create table PHANCONG_1
(
	MA_NVIEN char(9),
	MADA	 int,
	THOIGIAN float,
	constraint PK_PHANCONG_1 primary key (MA_NVIEN, MADA)
)

INSERT INTO PHANCONG_1 Select MANV, MADA, 10
from DEAN, NHANVIEN

sELECT * FROM NHANVIEN
SELECT TENNV
FROM NHANVIEN
UNION
SELECT TENTN
FROM THANNHAN

SELECT COUNT(DISTINCT PHG) AS SOLUONGNV
FROM NHANVIEN

SELECT PHG,COUNT(*) AS SOLUONGNV
FROM NHANVIEN
GROUP BY PHG

SELECT PHAI,COUNT(*) AS SOLUONGNV
FROM NHANVIEN
GROUP BY PHAI

SELECT PHG,AVG(LUONG) AS SOLUONGNV
FROM NHANVIEN
GROUP BY PHG





