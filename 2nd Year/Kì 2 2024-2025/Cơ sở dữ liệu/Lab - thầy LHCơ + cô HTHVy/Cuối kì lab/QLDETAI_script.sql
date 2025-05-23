﻿
USE master
ALTER DATABASE QLDETAI SET SINGLE_USER WITH ROLLBACK IMMEDIATE;

DROP DATABASE QLDETAI
GO

CREATE DATABASE QLDETAI
GO

USE QLDETAI
GO

--Q1--

CREATE TABLE KHOA
(
	MAKHOA char(5),
	TENKHOA nvarchar(40),
	NAMTL int CHECK (NAMTL > 1900),
	PHONG char(3),
	DIENTHOAI char(10),
	TRUONGKHOA char(5),
	NGAYNHANCHUC date,
	PRIMARY KEY (MAKHOA),
)
GO

ALTER TABLE KHOA
ADD CONSTRAINT U_TENKHOA
UNIQUE (TENKHOA)
GO


CREATE TABLE BOMON
(
	MABM char(5),
	TENBM nvarchar(40),
	PHONG char(3),
	DIENTHOAI char(10),
	TRUONGBM char(5),
	MAKHOA char(5),
	NGAYNHANCHUC date,
	PRIMARY KEY (MABM),
	FOREIGN KEY (MAKHOA) REFERENCES KHOA (MAKHOA)
)
GO

ALTER TABLE BOMON
ADD CONSTRAINT U_TENBM
UNIQUE (TENBM)
GO

CREATE TABLE GIAOVIEN
(
	MAGV char(5),
	HOTEN nvarchar(40),
	LUONG float CHECK (LUONG >= 0),
	PHAI nvarchar(3) CHECK (PHAI IN ('Nam', N'Nữ')),
	NGSINH date,
	DIACHI nvarchar(50),
	GVQLCM char(5),
	MABM char(5),
	PRIMARY KEY (MAGV),
	FOREIGN KEY (GVQLCM) REFERENCES GIAOVIEN (MAGV),
	FOREIGN KEY (MABM) REFERENCES BOMON (MABM)
)
GO

CREATE TABLE GV_DT
(
	MAGV char(5),
	DIENTHOAI char(10),
	PRIMARY KEY (MAGV, DIENTHOAI),
	FOREIGN KEY (MAGV) REFERENCES GIAOVIEN (MAGV)
)
GO

CREATE TABLE NGUOITHAN 
(
	MAGV char(5),
	TEN nvarchar(40),
	NGSINH date,
	PHAI nchar(3) CHECK (PHAI IN ('Nam', N'Nữ')),
	PRIMARY KEY (MAGV, TEN),
	FOREIGN KEY (MAGV) REFERENCES GIAOVIEN (MAGV)
)
GO

CREATE TABLE CHUDE
(
	MACD char(5),
	TENCD nvarchar(40),
	PRIMARY KEY (MACD)
)
GO

ALTER TABLE CHUDE
ADD CONSTRAINT U_TENCD
UNIQUE (TENCD)
GO

CREATE TABLE DETAI
(
	MADT char(5),
	TENDT nvarchar(40),
	CAPQL nvarchar(10),
	KINHPHI int CHECK (KINHPHI > 0),
	NGAYBD date,
	NGAYKT date,
	MACD char(5),
	GVCNDT char(5),
	PRIMARY KEY (MADT),
	FOREIGN KEY (MACD) REFERENCES CHUDE (MACD),
	FOREIGN KEY (GVCNDT) REFERENCES GIAOVIEN (MAGV)
)
GO

ALTER TABLE DETAI
ADD CONSTRAINT U_TENDT
UNIQUE (TENDT)
GO

CREATE TABLE CONGVIEC
(
	MADT char(5),
	SOTT int,
	TENCV nvarchar(40),
	NGAYBD date,
	NGAYKT date,
	PRIMARY KEY (MADT, SOTT),
	FOREIGN KEY (MADT) REFERENCES DETAI (MADT)
)
GO

CREATE TABLE THAMGIADT
(
	MAGV char(5),
	MADT char(5),
	STT int,
	PHUCAP float,
	KETQUA nvarchar(10),
	PRIMARY KEY (MAGV, MADT, STT),
	FOREIGN KEY (MAGV) REFERENCES GIAOVIEN (MAGV),
	FOREIGN KEY (MADT, STT) REFERENCES CONGVIEC (MADT, SOTT)
)
GO

ALTER TABLE KHOA
ADD CONSTRAINT
FK_KHOA_GIAOVIEN
FOREIGN KEY (TRUONGKHOA) REFERENCES GIAOVIEN (MAGV)
GO

ALTER TABLE BOMON
ADD CONSTRAINT
FK_BOMON_GIAOVIEN
FOREIGN KEY (TRUONGBM) REFERENCES GIAOVIEN (MAGV)
GO

--Q2--

INSERT INTO KHOA (MAKHOA, TENKHOA, NAMTL, PHONG, DIENTHOAI, TRUONGKHOA, NGAYNHANCHUC)
VALUES
	('CNTT', N'Công nghệ thông tin', 1995, 'B11', '0838123456', NULL, '02/20/2005'),
	('HH', N'Hóa học', 1980, 'B41', '0838456456', NULL, '10/15/2001'),
	('SH', N'Sinh học', 1980, 'B31', '0838454545', NULL, '09/18/2000'),
	('VL', N'Vật lý', 1976, 'B21', '0838223223', NULL, '09/18/2003');
GO

INSERT INTO BOMON (MABM, TENBM, PHONG, DIENTHOAI, TRUONGBM, MAKHOA, NGAYNHANCHUC)
VALUES
	('CNTT', N'Công nghệ tri thức', 'B15', '0838126126', NULL, 'CNTT', NULL),
	('HHC', N'Hóa hữu cơ', 'B44', '0838222222', NULL, 'HH', NULL),
	('HL', N'Hóa lý', 'B42', '0838878787', NULL, 'HH', NULL),
	('HPT', N'Hóa phân tích', 'B43', '0838777777', NULL, 'HH', '10/15/2007'),
	('HTTT', N'Hệ thống thông tin', 'B13', '0838125125', NULL, 'CNTT', '09/20/2004'),
	('MMT', N'Mạng máy tính', 'B16', '0838676767', NULL, 'CNTT', '05/15/2005'),
	('SH', N'Sinh hóa', 'B33', '0838898989', NULL, 'SH', NULL),
	('VLDT', N'Vật lý điện tử', 'B23', '0838234234', NULL, 'VL', NULL),
	('VLUD', N'Vật lý ứng dụng', 'B24', '0838454545', NULL, 'VL', '02/18/2006'),
	('VS', N'Vi sinh', 'B32', '0838909090', NULL, 'SH', '01/01/2007');
GO

INSERT INTO GIAOVIEN (MAGV, HOTEN, LUONG, PHAI, NGSINH, DIACHI, GVQLCM, MABM)
VALUES 
	('001', N'Nguyễn Hoài An', 2000.0, 'Nam', '02/15/1973', N'25/3 Lạc Long Quân, Q.10, TP HCM', NULL, 'MMT'),
	('002', N'Trần Trà Hương', 2500.0, N'Nữ', '06/20/1960', N'125 Trần Hưng Đạo, Q.1, TP HCM', NULL, 'HTTT'),
	('003', N'Nguyễn Ngọc Ánh', 2200.0, N'Nữ', '05/11/1975', N'12/21 Võ Văn Ngân, Thủ Đức, TP HCM', '002', 'HTTT'),
	('004', N'Trương Nam Sơn', 2300.0, 'Nam', '06/20/1959', N'215 Lý Thường Kiệt, TP Biên Hòa', NULL, 'VS'),
	('005', N'Lý Hoàng Hà', 2500.0, 'Nam', '10/23/1954', N'22/5 Nguyễn Xí, Q. Bình Thạnh, TP HCM', NULL, 'VLDT'),
	('006', N'Trần Bạch Tuyết', 1500.0, N'Nữ', '05/20/1980', N'127 Hùng Vương, TP Mỹ Tho', '004', 'VS'),
	('007', N'Nguyễn An Trung', 2100.0, 'Nam', '06/05/1976', N'3/2, TP Biên Hòa', NULL, 'HPT'),
	('008', N'Trần Trung Hiếu', 1800.0, 'Nam', '08/06/1977', N'22/11 Lý Thường Kiệt, TP Mỹ Tho', '007', 'HPT'),
	('009', N'Trần Hoàng Nam', 2000.0, 'Nam', '11/22/1975', N'234 Trần Não, An Phú, TP HCM', '001', 'MMT'),
	('010', N'Phạm Nam Thanh', 1500.0, 'Nam', '12/12/1980', N'221 Hùng Vương, Q.5, TP HCM', '007', 'HPT');
GO

UPDATE BOMON
SET TRUONGBM = '007'
WHERE TENBM = N'Hóa phân tích'
GO

UPDATE BOMON
SET TRUONGBM = '002'
WHERE TENBM = N'Hệ thống thông tin'
GO

UPDATE BOMON
SET TRUONGBM = '005'
WHERE TENBM = N'Vật lý ứng dụng'
GO

UPDATE BOMON
SET TRUONGBM = '004'
WHERE TENBM = N'Vi sinh'
GO

UPDATE GIAOVIEN
SET GVQLCM = '002'
WHERE MAGV = '003'
GO

UPDATE GIAOVIEN
SET GVQLCM = '004'
WHERE MAGV = '006'
GO

UPDATE GIAOVIEN
SET GVQLCM = '007'
WHERE MAGV = '008'
GO

UPDATE GIAOVIEN
SET GVQLCM = '001'
WHERE MAGV = '009'
GO

UPDATE GIAOVIEN
SET GVQLCM = '007'
WHERE MAGV = '010'
GO

UPDATE KHOA
SET TRUONGKHOA = '002'
WHERE MAKHOA = 'CNTT'
GO

UPDATE KHOA
SET TRUONGKHOA = '007'
WHERE MAKHOA = 'HH'
GO

UPDATE KHOA
SET TRUONGKHOA = '004'
WHERE MAKHOA = 'SH'
GO

UPDATE KHOA
SET TRUONGKHOA = '005'
WHERE MAKHOA = 'VL'
GO

INSERT INTO GV_DT (MAGV, DIENTHOAI)
VALUES
	('001', '0838912112'),
	('001', '0903123123'),
	('002', '0913454545'),
	('003', '0838121212'),
	('003', '0903656565'),
	('006', '0937125125'),
	('008', '0653717171'),
	('008', '0913232323');
GO

INSERT INTO NGUOITHAN (MAGV, TEN, NGSINH, PHAI)
VALUES
	('001', N'Hùng', '01/14/1990', 'Nam'),
	('001', N'Thủy', '12/08/1994', N'Nữ'),
	('003', N'Hà', '09/03/1998', N'Nữ'),
	('003', N'Thu', '09/03/1998', N'Nữ'),
	('007', N'Mai', '03/26/2003', N'Nữ'),
	('007', N'Vy', '02/14/2000', N'Nữ'),
	('008', N'Nam', '05/06/1991', 'Nam'),
	('009', N'An', '08/19/1996', 'Nam'),
	('010', N'Nguyệt', '01/14/2006', N'Nữ');
GO

INSERT INTO CHUDE (MACD, TENCD)
VALUES
	('NCPT', N'Nghiên cứu phát triển'),
	('QLGD', N'Quản lý giáo dục'),
	('UDCN', N'Ứng dụng công nghệ');
GO

INSERT INTO DETAI (MADT, TENDT, CAPQL, KINHPHI, NGAYBD, NGAYKT, MACD, GVCNDT)
VALUES
	('001', N'HTTT quản lý các trường ĐH', N'ĐHQG', 20.0, '10/20/2007', '10/20/2008', 'QLGD', '002'),
	('002', N'HTTT quản lý giáo vụ cho một Khoa', N'Trường', 20.0, '10/12/2000', '10/12/2001', 'QLGD', '002'),
	('003', N'Nghiên cứu chế tạo sợi Nano Platin', N'ĐHQG', 300.0, '05/15/2008', '05/15/2010', 'NCPT', '005'),
	('004', N'Tạo vật liệu sinh học bằng màng ối người', N'Nhà nước', 100.0, '01/01/2007', '12/31/2009', 'NCPT', '004'),
	('005', N'Ứng dụng hóa học xanh', N'Trường', 200.0, '10/10/2003', '12/10/2004', 'UDCN', '007'),
	('006', N'Nghiên cứu tế bào gốc', N'Nhà nước', 4000.0, '10/20/2006', '10/20/2009', 'NCPT', '004'),
	('007', N'HTTT quản lý thư viện ở các trường ĐH', N'Trường', 20.0, '05/10/2009', '05/10/2010', 'QLGD', '001');
GO

INSERT INTO CONGVIEC (MADT, SOTT, TENCV, NGAYBD, NGAYKT)
VALUES
	('001', 1, N'Khởi tạo và Lập kế hoạch', '10/20/2007', '12/20/2008'),
	('001', 2, N'Xác định yêu cầu', '12/21/2008', '03/21/2008'),
	('001', 3, N'Phân tích hệ thống', '03/22/2008', '05/22/2008'),
	('001', 4, N'Thiết kế hệ thống', '05/23/2008', '06/23/2008'),
	('001', 5, N'Cài đặt thử nghiệm', '06/24/2008', '10/20/2008'),
	('002', 1, N'Khởi tạo và Lập kế hoạch', '05/10/2009', '07/10/2009'),
	('002', 2, N'Xác định yêu cầu', '07/11/2009', '10/11/2009'),
	('002', 3, N'Phân tích hệ thống', '10/12/2009', '12/20/2009'),
	('002', 4, N'Thiết kế hệ thống', '12/21/2009', '03/22/2010'),
	('002', 5, N'Cài đặt thử nghiệm', '03/23/2010', '05/10/2010'),
	('006', 1, N'Lấy mẫu', '10/20/2006', '02/20/2007'),
	('006', 2, N'Nuôi cây', '02/21/2007', '08/21/2008');
GO

INSERT INTO THAMGIADT (MAGV, MADT, STT, PHUCAP, KETQUA)
VALUES
	('001', '002', 1, 0.0, NULL),
	('001', '002', 2, 2.0, NULL),
	('002', '001', 4, 2.0, N'Đạt'),
	('003', '001', 1, 1.0, N'Đạt'),
	('003', '001', 2, 0.0, N'Đạt'),
	('003', '001', 4, 1.0, N'Đạt'),
	('003', '002', 2, 0.0, NULL),
	('004', '006', 1, 0.0, N'Đạt'),
	('004', '006', 2, 1.0, N'Đạt'),
	('006', '006', 2, 1.5, N'Đạt'),
	('009', '002', 3, 0.5, NULL),
	('009', '002', 4, 1.5, NULL);
GO
