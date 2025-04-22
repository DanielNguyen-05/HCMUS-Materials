--Full Name: Nguyen Hai Dang
--Student ID: 23127165
--Class: 23CLC03
--ĐỀ ID: 01
use master
go
drop database QLBaiHat
go

create database QLBaiHat
go
use QLBaiHat
go

create table BAIHAT
(
    IDTheLoai varchar(10),
    IDBaiHat varchar(10),
    TenBaiHat nvarchar(30),
    IDTacGia int,
    constraint PK_BAIHAT primary key (IDTheLoai, IDBaiHat)
)

create table THELOAI
(
    IDTheLoai varchar(10),
    TenTheLoai nvarchar(30),
    IDBaiHatTieuBieu varchar(10),
    IDTheLoaiCha varchar(10),
    constraint PK_THELOAI primary key (IDTheLoai)
)

create table TACGIA
(
    IDTacGia int,
    HoTen nvarchar(30),
    IDTheLoaiSoTruongNhat varchar(10),
    IDBaiHatTieuBieuNhat varchar(10),
    constraint PK_TACGIA primary key (IDTacGia)
)

alter table BAIHAT
add constraint FK_BAIHAT_THELOAI foreign key (IDTheLoai) references THELOAI(IDTheLoai)
go

alter table BAIHAT
add constraint FK_BAIHAT_TACGIA foreign key (IDTacGia) references TACGIA(IDTacGia)
go

alter table THELOAI
add constraint FK_THELOAI_THELOAI foreign key (IDTheLoaiCha) references THELOAI(IDTheLoai)
go

alter table THELOAI
add constraint FK_THELOAI_BAIHAT foreign key (IDTheLoai, IDBaiHatTieuBieu) references BAIHAT(IDTheLoai, IDBaiHat)
go

alter table TACGIA
add constraint FK_TACGIA_BAIHAT foreign key (IDTheLoaiSoTruongNhat, IDBaiHatTieuBieuNhat) references BAIHAT(IDTheLoai, IDBaiHat)
go

insert into THELOAI values 
('TL01', N'Nhạc trữ tình', NULL, NULL),
('TL02', N'Nhạc cách mạng', NULL, NULL),
('TL00', N'Nhạc Việt Nam', NULL, NULL)
go 

insert into BAIHAT values 
('TL01', 'BH01', N'Ngẫu hứng lý qua cầu', NULL),
('TL01', 'BH02', N'Chuyến đò quê hương', NULL),
('TL02', 'BH01', N'Du kích sông Thao', NULL),
('TL02', 'BH02', N'Sợi nhớ sợi thương', NULL)
go 

insert into TACGIA values 
(1, N'Trần Tiến', 'TL01', 'BH01'),
(2, N'Đỗ Nhuận', 'TL02', 'BH01'),
(3, N'Phan Huỳnh Điểu', 'TL02', 'BH02'),
(4, N'Vi Nhật Tảo', 'TL01', 'BH02')
go

update THELOAI set IDTheLoaiCha = 'TL00', IDBaiHatTieuBieu = 'BH01' where IDTheLoai = 'TL01'
go
update THELOAI set IDTheLoaiCha = 'TL00', IDBaiHatTieuBieu = 'BH02' where IDTheLoai = 'TL02'
go 
update BAIHAT set IDTacGia = 1 where IDBaiHat = 'BH01' and IDTheLoai = 'TL01'
go
update BAIHAT set IDTacGia = 4 where IDBaiHat = 'BH02' and IDTheLoai = 'TL01'
go
update BAIHAT set IDTacGia = 2 where IDBaiHat = 'BH01' and IDTheLoai = 'TL02'
go
update BAIHAT set IDTacGia = 3 where IDBaiHat = 'BH02' and IDTheLoai = 'TL02'
go


--YÊU CẦU 2: TRUY VẤN
--Q1: Cho danh sách bài hát thuộc thể loại “nhạc trữ tình” của tác giả Đỗ Nhuận (1đ)
select bh.*
from BAIHAT bh
join THELOAI tl on bh.IDTheLoai = tl.IDTheLoai 
join TACGIA tg on bh.IDTacGia = tg.IDTacGia 
where tl.TenTheLoai = N'Nhạc cách mạng' and tg.HoTen = N'Đỗ Nhuận'

--Q2: Cho danh sách các thể loại chưa có bài hát nào trong thể loại đó (1đ)
select tl.*
from THELOAI tl
left join BAIHAT bh on bh.IDTheLoai = tl.IDTheLoai
where bh.IDBaiHat is NULL

--Q3: Cho danh sách tác giả (mã, họ tên, số bài hát) của mỗi tác giả. (1đ)
select tg.IDTacGia, tg.HoTen, count(bh.IDBaiHat) as SOBAIHAT
from TACGIA tg
left join BAIHAT bh on bh.IDTacGia = tg.IDTacGia
group by tg.IDTacGia, tg.HoTen