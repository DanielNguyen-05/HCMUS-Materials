--Đề: 01
--MSSV: 23127165
--Họ và tên: Nguyễn Hải Đăng
--Lớp: 23CLC03
--Mã máy: LAB52-WS33

--Yeu cau 1:
--1. Tạo CSDL
create database GK_23127165_QLPhim
go
use GK_23127165_QLPhim
go

--2. Tạo bảng và ràng buộc khoá chính
create table Actors 
(
	actor_id varchar(10),
	first_name nvarchar(30),
	last_name nvarchar(30),
	birthday date,
	Gender nvarchar(3) default N'Nữ',
	careerDefiningFilm varchar(10),
	constraint PK_Actors primary key (actor_id)
)

create table Movies
(
	movie_id varchar(10),
	title nvarchar(30),
	release_date date,
	director_id varchar(10),
	MovieRevenue int,
	ProductionBudget int,
	constraint PK_Movies primary key (movie_id)
)

create table Directors
(
	director_id varchar(10),
	Name nvarchar(30),
	DateOfBirth date,
	Nationality nvarchar(30),
	Gender nvarchar(3),
	best_id_movie varchar(10),
	constraint PK_Directors primary key (director_id)
)

create table Participation
(
	movie_id varchar(10),
	actor_id varchar(10),
	salary int,
	character nvarchar(10),
	constraint PK_Participation primary key (movie_id, actor_id)
)

--3. Tạo ràng buộc khoá ngoại
alter table Actors
add constraint FK_Actors_Movies foreign key (careerDefiningFilm) references Movies(movie_id)
go

alter table Movies
add constraint FK_Movies_Directors foreign key (director_id) references Directors(director_id)
go

alter table Participation
add constraint FK_Participation_Movies foreign key (movie_id) references Movies(movie_id)
go

alter table Participation
add constraint FK_Participation_Actors foreign key (actor_id) references Actors(actor_id)
go

--4. Nhập liệu
insert into Actors values
('A1', N'Robert', 'Downey', '1965-04-04', N'Nam', NULL),
('A2', N'Thuý Diễm', NULL, '1986-08-25', N'Nữ', NULL),
('A3', N'Stan Lee', NULL, NULL, N'Nam', NULL)

insert into Movies values
('M1', N'Iron Man', '2008-05-02', NULL, 585000000, 140000000),
('M2', N'Gạo nếp gạo tẻ', '2018-07-17', NULL, 100000, 30000)

insert into Directors values
('D1', N'Jon Favreau', '1966-09-15', N'Mỹ', N'Nam', NULL),
('D2', N'Trần Thanh Hương', '1974-10-19', N'Việt Nam', N'Nữ', 'M2')

insert into Participation values
('M1', 'A1', 100000, N'Chính'),
('M1', 'A3', 10000, N'Khách mời'),
('M2', 'A2', 10000, N'Chính')

update Actors set careerDefiningFilm = 'M1' where actor_id = 'A1'
go
update Movies set director_id = 'D1' where movie_id = 'M1'
go
update Movies set director_id = 'D2' where movie_id = 'M2'
go

--Yêu cầu 2: Truy vấn
--Câu 1:
select a.* 
from Actors a
join Participation p on p.actor_id = p.actor_id
where not exists (
	select 1 from Directors d
	join Movies m on d.director_id = m.director_id
	where d.Name = N'Jon Favreau' and m.movie_id = p.movie_id
)

--Câu 2:
select a.actor_id, a.first_name, a.last_name, a.careerDefiningFilm
from Actors a
join Participation p on a.actor_id = p.actor_id 
group by  a.actor_id, a.first_name, a.last_name, a.careerDefiningFilm
having count(distinct movie_id) > 2

--Câu 3:
select m.movie_id, m.title, m.ProductionBudget, sum(salary) as TotalSalary
from Movies m
join Participation p on m.movie_id = p.movie_id
where m.ProductionBudget > m.MovieRevenue
group by m.movie_id, m.title, m.ProductionBudget


