--MSSV: 23127165
--HOTEN: NGUYỄN HẢI ĐĂNG
--LOP: 23CLC03
--DE: GK

CREATE DATABASE QUANLY_BAIHAT23127165
GO

USE QUANLY_BAIHAT23127165

CREATE TABLE BAIHAT (
	IDTheLoai char(10), 
	IDBaiHat char(10),
	TenBaiHat nchar(30), 
	IDTacGia int,
	CONSTRAINT PK_ID PRIMARY KEY (IDTheLoai, IDBaiHat)
);

CREATE TABLE THELOAI(
	IDTheLoai char(10),
	TenTheLoai nchar(30), 
	IdBaiHatTieuBieu char(10) NULL, 
	IDTheLoaiCha char(10) NULL
	CONSTRAINT PK_THELOAI PRIMARY KEY (IDTheLoai)
);

CREATE TABLE TACGIA(
	IDTacGia int, 
	HoTen nchar(30), 
	IDTheLoaiSoTruongNhat char(10),
	IDBaiHatTieuBieuNhat char(10),
	CONSTRAINT PK_TACGIA PRIMARY KEY (IDTacGia)
);

--khoá ngoại
ALTER TABLE BAIHAT
ADD CONSTRAINT FK_TG
FOREIGN KEY (IDTacGia)
REFERENCES TACGIA(IDTacGia)

ALTER TABLE BAIHAT
ADD CONSTRAINT FK_TL
FOREIGN KEY (IDTheLoai)
REFERENCES THELOAI(IDTheLoai)

ALTER TABLE THELOAI
ADD CONSTRAINT FK_TL_BH
FOREIGN KEY (IDTheLoai, IDBaiHatTieuBieu)
REFERENCES BAIHAT(IDTheLoai, IDBaiHat)

ALTER TABLE THELOAI
ADD CONSTRAINT FK_TLCha
FOREIGN KEY (IDTheLoaiCha)
REFERENCES THELOAI(IDTheLoai)

ALTER TABLE TACGIA
ADD CONSTRAINT FK_NHAT
FOREIGN KEY (IDTheLoaiSoTruongNhat, IDBaiHatTieuBieuNhat)
REFERENCES BAIHAT(IDTheLoai, IDBaiHat)

-- Nhập dữ liệu
INSERT INTO THELOAI(IDTheLoai, TenTheLoai, IDTheLoaiCha, IdBaiHatTieuBieu) VALUES
('TL01', N'Nhạc Trữ Tình', NULL, NULL), 
('TL02', N'Nhạc cách mạng', NULL, NULL),
('TL00', N'Nhạc Việt Nam', NULL, NULL);

UPDATE THELOAI SET IDTheLoaiCha = 'TL00' WHERE IDTheLoai = 'TL01';
UPDATE THELOAI SET IDTheLoaiCha = 'TL00' WHERE IDTheLoai = 'TL02';

INSERT INTO BAIHAT(IDTheLoai, IDBaiHat, TenBaiHat, IDTacGia) VALUES
('TL01', 'BH01', N'Ngẫu hứng lý qua cầu', NULL), 
('TL01', 'BH02', N'Chuyến đò quê hương', NULL),
('TL02', 'BH01', N'Du kích sông Thao', NULL),
('TL01', 'BH02', N'Chuyến đò quê hương', NULL);

UPDATE THELOAI SET IdBaiHatTieuBieu = 'BH01' WHERE IDTheLoai = 'TL01';
UPDATE THELOAI SET IdBaiHatTieuBieu = 'BH02' WHERE IDTheLoai = 'TL02';

INSERT INTO TACGIA(IDTacGia, HoTen, IDTheLoaiSoTruongNhat, IDBaiHatTieuBieuNhat) VALUES
(1, N'Trần Tiến', 'TL01', 'BH01'), 
(2, N'Đỗ Nhuận', 'TL02', 'BH01'),
(3, N'Phan Huỳnh Điểu', 'TL02', 'BH02'), 
(4, N'Vi Nhật Tảo', 'TL01', 'BH02'); 

--TruyVan
SELECT bh.*
FROM THELOAI t1
JOIN BAIHAT bh ON  t1.IDTheLoai = bh.IDBaiHat
JOIN TACGIA tg ON bh.IDTacGia = tg.IDTacGia
WHERE t1.TenTheLoai = N'Nhạc trữ tình' AND tg.HoTen = N'Đỗ Nhuận'

SELECT t1.IDTheLoai, t1.TenTheLoai
FROM THELOAI t1
LEFT JOIN BAIHAT bh ON t1.IDTheLoai = bh.IDTheLoai
WHERE bh.IDBaiHat IS NULL

SELECT tg.IDTacGia, tg.HoTen, COUNT(bh.IDTacGia) AS SOBAIHAT
FROM BAIHAT bh, TACGIA tg
WHERE tg.IDTacGia = bh.IDTacGia
GROUP BY tg.IDTacGia, tg.HoTen


