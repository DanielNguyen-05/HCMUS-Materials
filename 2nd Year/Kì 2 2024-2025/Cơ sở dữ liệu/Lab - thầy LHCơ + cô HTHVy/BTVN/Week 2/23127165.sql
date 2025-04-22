-- 23127165 Nguyễn Hải Đăng 23CLC03

create database QLDeTaiSchema
GO
use QLDeTaiSchema

-- Create table THAMGIADT
create table THAMGIADT 
(
    MAGV char(3),
    MADT char(3),
    STT int,
    PHUCAP money,
    KETQUA nvarchar(100),
    CONSTRAINT PK_THAMGIADT PRIMARY KEY (MAGV, MADT, STT)
)

-- Create table KHOA
create table KHOA 
(
    MAKHOA char(10),
    TENKHOA nvarchar(100),
    NAMTL char(4),
    PHONG char(3),
    DIENTHOAI varchar(10) UNIQUE,
    TRUONGKHOA char(3),
    NGAYNHANCHUC date,
    CONSTRAINT PK_KHOA PRIMARY KEY (MAKHOA)
)

-- Create table BOMON
create table BOMON 
(
    MABM char(10),
    TENBM nvarchar(100),
    PHONG char(3),
    DIENTHOAI varchar(10) UNIQUE,
    TRUONGBM char(3),
    MAKHOA char(10),
    NGAYNHANCHUC date,
    CONSTRAINT PK_BOMON PRIMARY KEY (MABM)
)

-- Create table CONGVIEC
create table CONGVIEC 
(
    MADT char(3),
    SOTT int,
    TENCV nvarchar(100),
    NGAYBD date,
    NGAYKT date,
    CONSTRAINT PK_CONGVIEC PRIMARY KEY (MADT, SOTT)
)

-- Create table GIAOVIEN
create table GIAOVIEN 
(
    MAGV char(3),
    HOTEN nvarchar(100),
    LUONG money,
    PHAI nvarchar(3) CHECK (PHAI IN ('Nam', N'Nữ')),
    NGSINH date,
    DIACHI nvarchar(100),
    GVQLCM char(3),
    MABM char(10),
    CONSTRAINT PK_GIAOVIEN PRIMARY KEY (MAGV)
)

-- Create table GV_DT
create table GV_DT 
(
    MAGV char(3),
    DIENTHOAI varchar(10),
    CONSTRAINT PK_GV_DT PRIMARY KEY (MAGV, DIENTHOAI)
)

-- Create table DETAI
create table DETAI 
(
    MADT char(3),
    TENDT nvarchar(100),
    KINHPHI money,
    CAPQL nvarchar(50),
    NGAYBD date,
    NGAYKT date,
    MACD char(4),
    GVCNDT char(3),
    CONSTRAINT PK_DETAI PRIMARY KEY (MADT)
)

-- Create table NGUOITHAN
create table NGUOITHAN 
(
    MAGV char(3),
    TEN nvarchar(100),
    NGSINH date,
    PHAI nvarchar(3) CHECK (PHAI IN ('Nam', N'Nữ')),
    CONSTRAINT PK_NGUOITHAN PRIMARY KEY (MAGV, TEN)
)

-- Create table CHUDE
create table CHUDE 
(
    MACD char(4),
    TENCD nvarchar(100),
    CONSTRAINT PK_CHUDE PRIMARY KEY (MACD)
)

-- GIAOVIEN(GVQLCM) -> GIAOVIEN(MAGV)
alter table GIAOVIEN
ADD CONSTRAINT FK_GIAOVIEN_GVQLCM
FOREIGN KEY (GVQLCM) 
REFERENCES GIAOVIEN(MAGV)

-- GIAOVIEN(MABM) -> BOMON(MABM)
alter table GIAOVIEN
ADD CONSTRAINT FK_GIAOVIEN_BOMON 
FOREIGN KEY (MABM) 
REFERENCES BOMON(MABM)

-- GV_DT(MAGV) -> GIAOVIEN(MAGV)
alter table GV_DT
ADD CONSTRAINT FK_GV_DT 
FOREIGN KEY (MAGV) 
REFERENCES GIAOVIEN(MAGV)

-- BOMON(TRUONGBM) -> GIAOVIEN(MAGV)
alter table BOMON
ADD CONSTRAINT FK_BOMON_TRUONGBM 
FOREIGN KEY (TRUONGBM) 
REFERENCES GIAOVIEN(MAGV)

-- BOMON(MAKHOA) -> KHOA(MAKHOA)
alter table BOMON
ADD CONSTRAINT FK_BOMON_KHOA 
FOREIGN KEY (MAKHOA) 
REFERENCES KHOA(MAKHOA)

-- KHOA(TRUONGKHOA) -> GIAOVIEN(MAGV)
alter table KHOA
ADD CONSTRAINT FK_KHOA_TRUONGKHOA 
FOREIGN KEY (TRUONGKHOA) 
REFERENCES GIAOVIEN(MAGV)

-- DETAI(MACD) -> CHUDE(MACD)
alter table DETAI
ADD CONSTRAINT FK_DETAI_CHUDE 
FOREIGN KEY (MACD) 
REFERENCES CHUDE(MACD)

-- DETAI(GVCNDT) -> GIAOVIEN(MAGV)
alter table DETAI
ADD CONSTRAINT FK_DETAI_GVCNDT 
FOREIGN KEY (GVCNDT) 
REFERENCES GIAOVIEN(MAGV)

-- CONGVIEC(MADT) -> DETAI(MADT)
alter table CONGVIEC
ADD CONSTRAINT FK_CONGVIEC_DETAI 
FOREIGN KEY (MADT) 
REFERENCES DETAI(MADT)

-- THAMGIADT(MAGV) -> GIAOVIEN(MAGV)
alter table THAMGIADT
ADD CONSTRAINT FK_THAMGIADT_GIAOVIEN 
FOREIGN KEY (MAGV) 
REFERENCES GIAOVIEN(MAGV)

-- THAMGIADT(MADT, STT) -> CONGVIEC(MADT, SOTT)
alter table THAMGIADT
ADD CONSTRAINT FK_THAMGIADT_CONGVIEC
FOREIGN KEY (MADT, STT)
REFERENCES CONGVIEC(MADT, SOTT)

-- NGUOITHAN(MAGV) -> GIAOVIEN(MAGV)
alter table NGUOITHAN
ADD CONSTRAINT FK_NGUOITHAN_GIAOVIEN
FOREIGN KEY (MAGV)
REFERENCES GIAOVIEN(MAGV)

-- Insert data into CHUDE table
INSERT INTO CHUDE (MACD, TENCD) VALUES
('NCPT', N'Nghiên cứu phát triển'),
('QLGD', N'Quản lý giáo dục'),
('UDCN', N'Ứng dụng công nghệ');

-- Insert data into KHOA table
INSERT INTO KHOA (MAKHOA, TENKHOA, NAMTL, PHONG, DIENTHOAI, TRUONGKHOA, NGAYNHANCHUC) VALUES
('CNTT', N'Công nghệ thông tin', '1995', 'B11', '0838123456', NULL, '2005-02-20'),
('HH', N'Hóa học', '1980', 'B41', '0838456456', NULL, '2001-10-15'),
('SH', N'Sinh học', '1980', 'B31', '0838454545', NULL, '2000-10-11'),
('VL', N'Vật lý', '1976', 'B21', '0838223223', NULL, '2003-09-18');

-- Insert data into BOMON table
INSERT INTO BOMON (MABM, TENBM, PHONG, DIENTHOAI, TRUONGBM, MAKHOA, NGAYNHANCHUC) VALUES
('CNTT', N'Công nghệ tri thức', 'B15', '0838126126', NULL, 'CNTT', NULL),
('HHC', N'Hóa hữu cơ', 'B44', '838222222', NULL, 'HH', NULL),
('HL', N'Hóa lý', 'B42', '0838878787', NULL, 'HH', NULL),
('HPT', N'Hóa phân tích', 'B43', '0838777777', NULL, 'HH', '2007-10-15'),
('HTTT', N'Hệ thống thông tin', 'B13', '0838125125', NULL, 'CNTT', '2004-09-20'),
('MMT', N'Mạng máy tính', 'B16', '0838676767', NULL, 'CNTT', '2005-05-15'),
('SH', N'Sinh hóa', 'B33', '0838898989', NULL, 'SH', NULL),
('VLĐT', N'Vật lý điện tử', 'B23', '0838234234', NULL, 'VL', NULL),
('VLUD', N'Vật lý ứng dụng', 'B24', '0838454545', NULL, 'VL', '2006-02-18'),
('VS', N'Vi sinh', 'B32', '0838909090', NULL, 'SH', '2007-01-01');

-- Insert data into GIAOVIEN table
INSERT INTO GIAOVIEN (MAGV, HOTEN, LUONG, PHAI, NGSINH, DIACHI, GVQLCM, MABM) VALUES
('001', N'Nguyễn Hoài An', 2000.0, N'Nam', '1973-02-15', N'25/3 Lạc Long Quân, Q.10, TP HCM', NULL, 'MMT'),
('002', N'Trần Trà Hương', 2500.0, N'Nữ', '1960-06-20', N'125 Trần Hưng Đạo, Q.1, TP HCM', NULL, 'HTTT'),
('003', N'Nguyễn Ngọc Ánh', 2200.0, N'Nữ', '1975-05-11', N'12/21 Võ Văn Ngân Thủ Đức, TP HCM', '002', 'HTTT'),
('004', N'Trương Nam Sơn', 2300.0, N'Nam', '1959-06-20', N'215 Lý Thường Kiệt,TP Biên Hòa', NULL, 'VS'),
('005', N'Lý Hoàng Hà', 2500.0, N'Nam', '1954-10-23', N'22/5 Nguyễn Xí, Q.Bình Thạnh, TP HCM', NULL, 'VLĐT'),
('006', N'Trần Bạch Tuyết', 1500.0, N'Nữ', '1980-05-20', N'127 Hùng Vương, TP Mỹ Tho', '004', 'VS'),
('007', N'Nguyễn An Trung', 2100.0, N'Nam', '1976-06-05', N'234 3/2, TP Biên Hòa', NULL, 'HPT'),
('008', N'Trần Trung Hiếu', 1800.0, N'Nam', '1977-08-06', N'22/11 Lý Thường Kiệt, TP Mỹ Tho', '007', 'HPT'),
('009', N'Trần Hoàng Nam', 2000.0, N'Nam', '1975-11-22', N'234 Trấn Não, An Phú, TP HCM', '001', 'MMT'),
('010', N'Phạm Nam Thanh', 1500.0, N'Nam', '1980-12-12', N'221 Hùng Vương, Q.5, TP HCM', '007', 'HPT');

-- Update TRUONGKHOA and TRUONGBM after inserting GIAOVIEN
UPDATE KHOA SET TRUONGKHOA = '002' WHERE MAKHOA = 'CNTT';
UPDATE KHOA SET TRUONGKHOA = '007' WHERE MAKHOA = 'HH';
UPDATE KHOA SET TRUONGKHOA = '004' WHERE MAKHOA = 'SH';
UPDATE KHOA SET TRUONGKHOA = '005' WHERE MAKHOA = 'VL';

UPDATE BOMON SET TRUONGBM = '002' WHERE MABM = 'CNTT';
UPDATE BOMON SET TRUONGBM = '007' WHERE MABM = 'HHC';
UPDATE BOMON SET TRUONGBM = '007' WHERE MABM = 'HL';
UPDATE BOMON SET TRUONGBM = '007' WHERE MABM = 'HPT';
UPDATE BOMON SET TRUONGBM = '002' WHERE MABM = 'HTTT';
UPDATE BOMON SET TRUONGBM = '001' WHERE MABM = 'MMT';
UPDATE BOMON SET TRUONGBM = '004' WHERE MABM = 'SH';
UPDATE BOMON SET TRUONGBM = '005' WHERE MABM = 'VLĐT';
UPDATE BOMON SET TRUONGBM = '005' WHERE MABM = 'VLUD';
UPDATE BOMON SET TRUONGBM = '004' WHERE MABM = 'VS';


-- Insert data into GV_DT table
INSERT INTO GV_DT (MAGV, DIENTHOAI) VALUES
('001', '0838912112'),
('001', '0903123123'),
('002', '0913454545'),
('003', '0838121212'),
('003', '0903656565'),
('003', '0937125125'),
('006', '0937888888'),
('008', '0653717171'),
('008', '0913232323');

-- Insert data into DETAI table
INSERT INTO DETAI (MADT, TENDT, KINHPHI, CAPQL, NGAYBD, NGAYKT, MACD, GVCNDT) VALUES
('001', N'HTTT quản lý các trường ĐH', 20.0, N'ĐHQG', '2007-10-20', '2008-10-20', 'QLGD', '002'),
('002', N'HTTT quản lý giáo vụ cho một Khoa', 20.0, N'Trường', '2000-10-12', '2001-10-12', 'QLGD', '002'),
('003', N'Nghiên cứu chế tạo sợi Nanô Platin', 300.0, N'ĐHQG', '2008-05-15', '2010-05-15', 'NCPT', '005'),
('004', N'Tạo vật liệu sinh học bằng màng ối người', 100.0, N'Nhà nước', '2007-01-01', '2009-12-31', 'NCPT', '004'),
('005', N'Ứng dụng hóa học xanh', 200.0, N'Trường', '2003-10-10', '2004-12-10', 'UDCN', '007'),
('006', N'Nghiên cứu tế bào gốc', 4000.0, N'Nhà nước', '2006-10-20', '2009-10-20', 'NCPT', '004'),
('007', N'HTTT quản lý thư viện ở các trường ĐH', 20.0, N'Trường', '2009-05-10', '2010-05-10', 'QLGD', '001');

-- Insert data into CONGVIEC table
INSERT INTO CONGVIEC (MADT, SOTT, TENCV, NGAYBD, NGAYKT) VALUES
('001', 1, N'Khởi tạo và Lập kế hoạch', '2007-10-20', '2008-12-20'),
('001', 2, N'Xác định yêu cầu', '2008-12-21', '2008-03-21'),
('001', 3, N'Phân tích hệ thống', '2008-03-22', '2008-05-22'),
('001', 4, N'Thiết kế hệ thống', '2008-05-23', '2008-06-23'),
('001', 5, N'Cài đặt thử nghiệm', '2008-06-24', '2008-10-20'),
('002', 1, N'Khởi tạo và Lập kế hoạch', '2009-05-10', '2009-07-10'),
('002', 2, N'Xác định yêu cầu', '2009-07-11', '2009-10-11'),
('002', 3, N'Phân tích hệ thống', '2009-10-12', '2009-12-20'),
('002', 4, N'Thiết kế hệ thống', '2009-12-21', '2010-03-22'),
('002', 5, N'Cài đặt thử nghiệm', '2010-03-23', '2010-05-10'),
('006', 1, N'Lấy mẫu', '2006-10-20', '2007-02-20'),
('006', 2, N'Nuôi cấy', '2007-02-21', '2008-08-21');

-- Insert data into NGUOITHAN table
INSERT INTO NGUOITHAN (MAGV, TEN, NGSINH, PHAI) VALUES
('001', N'Hùng', '1990-01-14', N'Nam'),
('001', N'Thủy', '1994-12-08', N'Nữ'),
('003', N'Hà', '1998-09-03', N'Nữ'),
('003', N'Thu', '1998-09-03', N'Nữ'),
('007', N'Mai', '2003-03-26', N'Nữ'),
('007', N'Vy', '2000-02-14', N'Nữ'),
('008', N'Nam', '1991-05-06', N'Nam'),
('009', N'An', '1996-08-19', N'Nam'),
('010', N'Nguyệt', '2006-01-14', N'Nữ');

-- Insert data into THAMGIADT table
INSERT INTO THAMGIADT (MAGV, MADT, STT, PHUCAP, KETQUA) VALUES
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
