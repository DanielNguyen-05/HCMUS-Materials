--Full Name: Nguyễn Hải Đăng
--Student ID: 23127165
--Class: 23CLC03
--Ma de: 01
use master
go
drop database QLNhanVien
go

create database QLNhanVien
go
use QLNhanVien
go

--1. (2.25đ) Tạo bảng và tạo ràng buộc khóa chính cho các bảng trên.
create table PHONGBAN
(
    MaPhongBan varchar(4),
    TenPhongBan nvarchar(30),
    DiaDiem nvarchar(4),
    TruongPhong varchar(4),
    constraint PK_PHONGBAN primary key (MaPhongBan)
)

create table DEAN
(
    MaDeAn varchar(4),
    TenDeAn nvarchar(30),
    ThoiGian varchar(3),
    MaPhongBan varchar(4),
    TruongDeAn varchar(4),
    constraint PK_DEAN primary key (MaDeAn)
)

create table NHANVIEN 
(
    MaNV varchar(4),
    MaPhong varchar(4),
    HoTen nvarchar(30),
    NgaySinh date,
    GioiTinh nvarchar(3),
    Luong float,
    constraint PK_NHANVIEN primary key (MaNV, MaPhong)
)

--2. (2.25đ) Tạo ràng buộc khóa ngoại cho các bảng trên.
alter table PHONGBAN
add constraint FK_PHONGBAN_NHANVIEN foreign key (TruongPhong, MaPhongBan) references NHANVIEN(MaNV, MaPhong)

alter table DEAN
add constraint FK_DENAN_PHONGBAN foreign key (MaPhongBan) references PHONGBAN(MaPhongBan)

alter table DEAN
add constraint FK_DEAN_NHANVIEN foreign key (TruongDeAn, MaPhongBan) references NHANVIEN(MaNV, MaPhong)

alter table NHANVIEN
add constraint FK_NHANVIEN_PHONGBAN foreign key (MaPhong) references PHONGBAN(MaPhongBan)

--3. (2.00đ) Nhập các dòng dữ liệu sau vào các bảng tương ứng.
insert into DEAN values
('DA01', N'Ngôi nhà thông minh', '120', NULL, NULL),
('DA02', N'Hành tinh xanh', '220', NULL, NULL),
('DA03', N'Công viên xanh', '100', NULL, NULL)
go

insert into PHONGBAN values
('P001', N'Nghiên cứu', 'C444', NULL),
('P002', N'Kế hoạch', 'B234', NULL),
('P003', N'Nhân sự', 'D111', NULL)
go

SET DATEFORMAT DMY;
insert into NHANVIEN values
('NV01', 'P001', N'Trần Hải', '12/2/1999', N'Nam', 2500),
('NV02', 'P001', N'Lê Anh Đào', '28/2/1987', N'Nữ', 3000),
('NV01', 'P002', N'Lý Khanh', '6/6/1960', N'Nam', 1000),
('NV02', 'P002', N'Phan Minh Trí', '6/6/1960', N'Nam', 2500),
('NV03', 'P002', N'Nguyễn Lan', '7/3/1982', N'Nữ', 3000),
('NV01', 'P003', N'Vũ Bình Phương', '17/3/1980', N'Nam', 3000),
('NV02', 'P003', N'Đặng Khải Minh', '22/10/1980', N'Nam', 1400);
go

update PHONGBAN set TruongPhong = 'NV02' where MaPhongBan = 'P001'
go
update PHONGBAN set TruongPhong = 'NV03' where MaPhongBan = 'P002'
go
update PHONGBAN set TruongPhong = 'NV01' where MaPhongBan = 'P003'
go

update DEAN set MaPhongBan = 'P001', TruongDeAn = 'NV02' where MaDeAn = 'DA01'
go
update DEAN set MaPhongBan = 'P002', TruongDeAn = 'NV01' where MaDeAn = 'DA02'
go
update DEAN set MaPhongBan = 'P002', TruongDeAn = 'NV02' where MaDeAn = 'DA03'
go

--4. (1.00đ) Cho biết thông tin mã và tên nhân viên vừa là trưởng phòng vừa là trưởng đề án.
select nv.MaNV, nv.HoTen, pb.TenPhongBan, da.TenDeAn
from NHANVIEN nv
join PHONGBAN pb on pb.TruongPhong = nv.MaNV and pb.MaPhongBan = nv.MaPhong
join DEAN da on da.TruongDeAn = nv.MaNV and da.MaPhongBan = nv.MaPhong
group by nv.MaNV, nv.HoTen, pb.TenPhongBan, da.TenDeAn

--5. (1.25đ) Cho biết thông tin mã, tên phòng, họ tên trưởng phòng và số lượng nhân viên của từng phòng ban.
select pb.MaPhongBan, pb.TenPhongBan, nv.HoTen, count(nv2.MaNV) as SoLuongNhanVien
from PHONGBAN pb
left join NHANVIEN nv on nv.MaNV = pb.TruongPhong and nv.MaPhong = pb.MaPhongBan
left join NHANVIEN nv2 on nv2.MaPhong = pb.MaPhongBan
group by pb.MaPhongBan, pb.TenPhongBan, nv.HoTen

--6. (1.25đ) Cho biết thông tin mã, tên phòng ban phụ trách từ 2 đề án trở lên.
select pb.MaPhongBan, pb.TenPhongBan
from PHONGBAN pb
join DEAN da on pb.MaPhongBan = da.MaPhongBan
group by pb.MaPhongBan, pb.TenPhongBan having count(pb.MaPhongBan) >= 2