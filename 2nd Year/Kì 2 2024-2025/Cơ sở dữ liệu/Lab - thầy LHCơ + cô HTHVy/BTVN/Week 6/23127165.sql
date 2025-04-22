--Q58. Cho biết tên giáo viên nào mà tham gia đề tài đủ tất cả các chủ đề.
--EXCEPT
select GV.HOTEN
from GIAOVIEN GV
where not exists(select CHUDE.MACD from CHUDE
					except
				select DT.MACD 
				from DETAI DT, THAMGIADT TGDT
				where GV.MAGV = TGDT.MAGV and TGDT.MADT = DT.MADT
				);

-- NOT EXISTS
select GV.HOTEN
from GIAOVIEN GV
where not exists(
				select * from CHUDE CD
				where not exists(select * 
				from DETAI DT, THAMGIADT TGDT
				where GV.MAGV = TGDT.MAGV and TGDT.MADT = DT.MADT and CD.MACD = DT.MACD)
				);

-- COUNT
select GV.HOTEN
from GIAOVIEN GV, THAMGIADT TGDT, DETAI DT
where GV.MAGV = TGDT.MAGV and TGDT.MADT = DT.MADT
group by GV.HOTEN
having count(distinct DT.MACD) = (
								select count(CHUDE.MACD)
								from CHUDE
								);

--Q59. Cho biết tên đề tài nào mà được tất cả các giáo viên của bộ môn HTTT tham gia.
--EXCEPT
select DT1.TENDT
from DETAI DT1
where not exists( 
				select GV.MAGV
				from GIAOVIEN GV
				where GV.MABM = 'HTTT'
				except
				select TGDT.MAGV
				from THAMGIADT TGDT
				where TGDT.MADT = DT1.MADT
				);

--NOT EXISTS
select DT1.TENDT
from DETAI DT1
where not exists( 
				select *
				from GIAOVIEN GV
				where GV.MABM = 'HTTT' and not exists(
				select *
				from THAMGIADT TGDT
				where TGDT.MADT = DT1.MADT and GV.MAGV = TGDT.MAGV
				)
	);

--COUNT
select DT.TENDT
from DETAI DT, GIAOVIEN GV, THAMGIADT TG
where GV.MABM = 'HTTT' and GV.MAGV = TG.MAGV and TG.MADT = DT.MADT
group by DT.TENDT
having count(distinct TG.MAGV) = (
								select count(GV2.MAGV) 
								from GIAOVIEN GV2
								where GV2.MABM = 'HTTT' );


--Q60. Cho biết tên đề tài có tất cả giảng viên bộ môn “Hệ thống thông tin” tham gia
--EXCEPT
select DT1.TENDT
from DETAI DT1
where not exists( 
				select GV.MAGV
				from GIAOVIEN GV, BOMON BM
				where BM.TENBM = N'Hệ thống thông tin' and BM.MABM = GV.MABM
				except
				select TGDT.MAGV
				from THAMGIADT TGDT
				where TGDT.MADT = DT1.MADT
				);

-- NOT EXISTS
select DT1.TENDT
from DETAI DT1
where not exists( 
				select *
				from GIAOVIEN GV, BOMON BM
				where BM.TENBM = N'Hệ thống thông tin' and BM.MABM = GV.MABM
				and not exists(
				select *
				from THAMGIADT TGDT
				where TGDT.MADT = DT1.MADT and GV.MAGV = TGDT.MAGV
				)
	);

-- COUNT
select DT.TENDT
from DETAI DT, GIAOVIEN GV, THAMGIADT TG, BOMON BM
where BM.TENBM = N'Hệ thống thông tin' and GV.MABM = BM.MABM and GV.MAGV = TG.MAGV and TG.MADT = DT.MADT
group by DT.TENDT
having count(distinct TG.MAGV) = (
								select count(GV2.MAGV) 
								from GIAOVIEN GV2, BOMON BM2
								where BM2.TENBM = N'Hệ thống thông tin' and GV2.MABM = BM2.MABM );

--Q61. Cho biết giáo viên nào đã tham gia tất cả các đề tài có mã chủ đề là QLGD.
-- EXCEPT
select distinct TG1.MAGV, GV.HOTEN
from THAMGIADT TG1, GIAOVIEN GV
where TG1.MAGV = GV.MAGV and not exists (
						( select MADT from DETAI where MACD = N'QLGD')
						except
						( select MADT
						from THAMGIADT TG2
						where TG2.MAGV = TG1.MAGV ));

--NOT EXIST
select distinct TG1.MAGV, GV.HOTEN
from THAMGIADT TG1, GIAOVIEN GV
where TG1.MAGV = GV.MAGV	and not exists (
						 select *  from DETAI DT where DT.MACD = N'QLGD'
						and not exists(select *
						from THAMGIADT TG2
						where TG2.MAGV = TG1.MAGV and DT.MADT = TG2.MADT)
						);

--COUNT
select GV1.HOTEN
from GIAOVIEN GV1, THAMGIADT TG1, DETAI DT1
where GV1.MAGV = TG1.MAGV and TG1.MADT = DT1.MADT and DT1.MACD = N'QLGD'
group by GV1.HOTEN
having count (distinct DT1.MADT) = (
									select count(DT2.MACD)
									from DETAI DT2
									where DT2.MACD = N'QLGD');


--Q62. Cho biết tên giáo viên nào tham gia tất cả các đề tài mà giáo viên Trần Trà Hương đã tham gia.
--EXCEPT
select GV1.HOTEN
from GIAOVIEN GV1
where GV1.HOTEN != N'Trần Trà Hương' and  not exists( 
				select TGDT.MADT
				from THAMGIADT TGDT, GIAOVIEN GV
				where GV.HOTEN = N'Trần Trà Hương' and GV.MAGV = TGDT.MAGV
				except
				select TGDT2.MADT
				from THAMGIADT TGDT2
				where GV1.MAGV = TGDT2.MAGV
				);

-- NOT EXISTS
select GV1.HOTEN
from GIAOVIEN GV1
where GV1.HOTEN != N'Trần Trà Hương' and  not exists( 
				select TGDT.MADT
				from THAMGIADT TGDT, GIAOVIEN GV
				where GV.HOTEN = N'Trần Trà Hương' and GV.MAGV = TGDT.MAGV
				and not exists(
				select TGDT2.MADT
				from THAMGIADT TGDT2
				where GV1.MAGV = TGDT2.MAGV and TGDT.MADT = TGDT2.MADT)
				);

--COUNT
select GV2.HOTEN
from GIAOVIEN GV2, THAMGIADT TG2
where GV2.HOTEN != N'Trần Trà Hương' and GV2.MAGV = TG2.MAGV and TG2.MADT in (select TG1.MADT
										from GIAOVIEN GV1, THAMGIADT TG1
										where GV1.HOTEN = N'Trần Trà Hương' and GV1.MAGV = TG1.MAGV)
group by GV2.HOTEN
having count(distinct TG2.MADT) = (select count(TG1.MADT)
										from GIAOVIEN GV1, THAMGIADT TG1
										where GV1.HOTEN = N'Trần Trà Hương' and GV1.MAGV = TG1.MAGV);

--Q63. Cho biết tên đề tài nào mà được tất cả các giáo viên của bộ môn Hóa Hữu Cơ tham gia.
--EXCEPT
select DT1.TENDT
from DETAI DT1
where not exists( 
				select GV.MAGV
				from GIAOVIEN GV, BOMON BM
				where BM.TENBM = N'Hóa hữu cơ' and BM.MABM = GV.MABM
				except
				select TGDT.MAGV
				from THAMGIADT TGDT
				where TGDT.MADT = DT1.MADT
				);

--NOT EXISTS
select DT1.TENDT
from DETAI DT1
where not exists( 
				select GV.MAGV
				from GIAOVIEN GV, BOMON BM
				where BM.TENBM = N'Hóa hữu cơ' and BM.MABM = GV.MABM
				and not exists(
				select TGDT.MAGV
				from THAMGIADT TGDT
				where TGDT.MADT = DT1.MADT and GV.MAGV = TGDT.MAGV)
				);

-- COUNT
select DT1.TENDT
from DETAI DT1, THAMGIADT TG1
where TG1.MAGV in (select GV1.MAGV
					from GIAOVIEN GV1, BOMON BM1
					where BM1.TENBM = N'Hóa hữu cơ' and BM1.MABM = GV1.MABM)
group by DT1.TENDT
having count(distinct TG1.MAGV) = (
								select count(GV2.MAGV)
								from GIAOVIEN GV2, BOMON BM2
								where BM2.TENBM = N'Hóa hữu cơ' and BM2.MABM = GV2.MABM
									);

--Q64. Cho biết tên giáo viên nào mà tham gia tất cả các công việc của đề tài 006.
--EXCEPT
select GV.HOTEN
from GIAOVIEN GV
where not exists(select CV.SOTT
				from CONGVIEC CV
				where CV.MADT = '006'	
				except
				select TGDT.STT
				from THAMGIADT TGDT
				where GV.MAGV = TGDT.MAGV and TGDT.MADT = '006');

--NOT EXISTS
select GV.HOTEN
from GIAOVIEN GV
where not exists(select * 
				from CONGVIEC CV
				where CV.MADT = '006'	
				and not exists(
				select *
				from THAMGIADT TGDT
				where GV.MAGV = TGDT.MAGV and TGDT.MADT = '006' and CV.STT = TGDT.STT));

-- COUNT				
select GV.HOTEN
from GIAOVIEN GV, THAMGIADT TG
where GV.MAGV = TG.MAGV and TG.MADT = '006'
group by GV.HOTEN
having count(distinct TG.STT) = (select count(CV.SOTT)
								from CONGVIEC CV
								where CV.MADT = '006');

--Q65. Cho biết giáo viên nào đã tham gia tất cả các đề tài của chủ đề Ứng dụng công nghệ.
--EXCEPT
select GV.HOTEN
from GIAOVIEN GV
where not exists(select DT.MADT
				from DETAI DT, CHUDE CD
				where CD.TENCD = N'Ứng dụng công nghệ' and CD.MACD = DT.MACD
				except
				select TGDT.MADT
				from THAMGIADT TGDT
				where TGDT.MAGV = GV.MAGV
				);

--NOT EXISTS
select GV.HOTEN
from GIAOVIEN GV
where not exists(select *
				from DETAI DT, CHUDE CD
				where CD.TENCD = N'Ứng dụng công nghệ' and CD.MACD = DT.MACD
				and not exists(
				select *
				from THAMGIADT TGDT
				where TGDT.MAGV = GV.MAGV and DT.MADT = TGDT.MADT)
				);

-- COUNT
select GV.HOTEN
from GIAOVIEN GV, THAMGIADT TG, CHUDE CD, DETAI DT
where CD.TENCD = N'Ứng dụng công nghệ' and CD.MACD = DT.MACD and DT.MADT = TG.MADT and TG.MAGV = GV.MAGV
group by GV.HOTEN
having count(distinct TG.MADT) = (select count(DT.MADT) 
								from DETAI DT, CHUDE CD
								where CD.TENCD = N'Ứng dụng công nghệ' and CD.MACD = DT.MACD);

--Q66. Cho biết tên giáo viên nào đã tham gia tất cả các đề tài của do Trần Trà Hương làm chủ nhiệm.
--EXCEPT
select GV1.HOTEN
from GIAOVIEN GV1
where not exists(	select DT.MADT
					from DETAI DT, GIAOVIEN GV
					where GV.HOTEN = N'Trần Trà Hương' and GV.MAGV = DT.GVCNDT
					except
					select TGDT.MADT
					from THAMGIADT TGDT
					where TGDT.MAGV = GV1.MAGV
				);

--NOT EXISTS
select GV1.HOTEN
from GIAOVIEN GV1
where not exists(	select DT.MADT
					from DETAI DT, GIAOVIEN GV
					where GV.HOTEN = N'Trần Trà Hương' and GV.MAGV = DT.GVCNDT
					and not exists(
					select TGDT.MADT
					from THAMGIADT TGDT
					where TGDT.MAGV = GV1.MAGV and DT.MADT = TGDT.MADT)
				);

--COUNT
select GV.HOTEN
from GIAOVIEN GV, THAMGIADT TG
where GV.MAGV = TG.MAGV and TG.MADT in (select DT.MADT
										from DETAI DT, GIAOVIEN GV
										where GV.HOTEN = N'Trần Trà Hương' and GV.MAGV = DT.GVCNDT)
group by GV.HOTEN
having count(distinct TG.MADT) = (select count(DT.MADT)
										from DETAI DT, GIAOVIEN GV
										where GV.HOTEN = N'Trần Trà Hương' and GV.MAGV = DT.GVCNDT);

--Q67. Cho biết tên đề tài nào mà được tất cả các giáo viên của khoa CNTT tham gia.
--EXCEPT
select DT.TENDT
from DETAI DT
where not exists(select GV.MAGV
				from GIAOVIEN GV, BOMON BM, KHOA K
				where GV.MABM = BM.MABM and BM.MAKHOA = K.MAKHOA and K.MAKHOA = N'CNTT'  
				except
				select TGDT.MAGV
				from THAMGIADT TGDT
				where TGDT.MADT = DT.MADT
				);

-- NOT EXISTS
select DT.TENDT
from DETAI DT
where not exists(select *
				from GIAOVIEN GV, BOMON BM, KHOA K
				where GV.MABM = BM.MABM and BM.MAKHOA = K.MAKHOA and K.MAKHOA = N'CNTT' 
				and not exists(
				select *
				from THAMGIADT TGDT
				where TGDT.MADT = DT.MADT and GV.MAGV = TGDT.MAGV)
				);

-- COUNT
select DT.TENDT
from DETAI DT, THAMGIADT TG
where DT.MADT = TG.MADT and TG.MAGV in (select GV.MAGV
									from GIAOVIEN GV, BOMON BM, KHOA K
									where GV.MABM = BM.MABM and BM.MAKHOA = K.MAKHOA and K.MAKHOA = N'CNTT') 
group by DT.TENDT
having count(distinct TG.MAGV) = (select count(GV.MAGV)
					from GIAOVIEN GV, BOMON BM, KHOA K
					where GV.MABM = BM.MABM and BM.MAKHOA = K.MAKHOA and K.MAKHOA = N'CNTT'); 

--Q68. Cho biết tên giáo viên nào mà tham gia tất cả các công việc của đề tài Nghiên cứu tế bào gốc.
--EXCEPT
select GV.HOTEN
from GIAOVIEN GV
where not exists(select CV.SOTT
				from CONGVIEC CV, DETAI DT
				where DT.TENDT = N'Nghiên cứu tế bào gốc' and DT.MADT = CV.MADT	
				except
				select TGDT.STT
				from THAMGIADT TGDT, DETAI DT2
				where DT2.TENDT = N'Nghiên cứu tế bào gốc' and DT2.MADT = TGDT.MADT and GV.MAGV = TGDT.MAGV);

-- NOT EXISTS
select GV.HOTEN
from GIAOVIEN GV
where not exists(select *
				from CONGVIEC CV, DETAI DT
				where DT.TENDT = N'Nghiên cứu tế bào gốc' and DT.MADT = CV.MADT	
				and not exists( 
				select *
				from THAMGIADT TGDT, DETAI DT2
				where DT2.TENDT = N'Nghiên cứu tế bào gốc' and DT2.MADT = TGDT.MADT 
				and GV.MAGV = TGDT.MAGV and TGDT.STT = CV.SOTT)
			);

--COUNT
select GV.HOTEN
from GIAOVIEN GV, DETAI DT, THAMGIADT TG
where GV.MAGV = TG.MAGV and TG.MADT = DT.MADT and DT.TENDT = N'Nghiên cứu tế bào gốc'
group by GV.HOTEN
having count(distinct TG.STT) = (select count(CV.SOTT)
				from CONGVIEC CV, DETAI DT1
				where DT1.TENDT = N'Nghiên cứu tế bào gốc' and DT1.MADT = CV.MADT);

--Q69. Tìm tên các giáo viên được phân công làm tất cả các đề tài có kinh phí trên 100 triệu?
--EXCEPT
select GV.HOTEN
from GIAOVIEN GV
where not exists(select DT.MADT
				from DETAI DT
				where DT.KINHPHI > 100 
				except
				select TGDT.MADT
				from THAMGIADT TGDT
				where GV.MAGV = TGDT.MAGV
				);

-- NOT EXISTS
select GV.HOTEN
from GIAOVIEN GV
where not exists(select *
				from DETAI DT
				where DT.KINHPHI > 100 
				and not exists(
				select *
				from THAMGIADT TGDT
				where GV.MAGV = TGDT.MAGV and DT.MADT = TGDT.MADT)
				);

--COUNT
select GV.HOTEN
from GIAOVIEN GV, THAMGIADT TG
where GV.MAGV = TG.MAGV and TG.MADT in (select DT1.MADT
					from DETAI DT1
					where DT1.KINHPHI > 100) 
group by GV.HOTEN
having count(distinct TG.MADT) = (select count(DT1.MADT)
					from DETAI DT1
					where DT1.KINHPHI > 100); 

--Q70. Cho biết tên đề tài nào mà được tất cả các giáo viên của khoa Sinh Học tham gia.
--EXCEPT
select DT.TENDT
from DETAI DT
where not exists(select GV.MAGV
				from GIAOVIEN GV, BOMON BM, KHOA K
				where GV.MABM = BM.MABM and BM.MAKHOA = K.MAKHOA and K.TENKHOA = N'Sinh học'
				except
				select TGDT.MAGV
				from THAMGIADT TGDT
				where TGDT.MADT = DT.MADT
				);

--NOT EXISTST
select DT.TENDT
from DETAI DT
where not exists(select *
				from GIAOVIEN GV, BOMON BM, KHOA K
				where GV.MABM = BM.MABM and BM.MAKHOA = K.MAKHOA and K.TENKHOA = N'Sinh học'
				and not exists(
				select *
				from THAMGIADT TGDT
				where TGDT.MADT = DT.MADT and GV.MAGV = TGDT.MAGV)
				);

-- COUNT
select DT.TENDT
from DETAI DT, THAMGIADT TG
where DT.MADT = TG.MADT and TG.MAGV in (select GV.MAGV
					from GIAOVIEN GV, BOMON BM, KHOA K
					where GV.MABM = BM.MABM and BM.MAKHOA = K.MAKHOA and K.TENKHOA = N'Sinh học')
group by DT.TENDT
having count(distinct TG.MAGV) = (select count(GV.MAGV)
					from GIAOVIEN GV, BOMON BM, KHOA K
					where GV.MABM = BM.MABM and BM.MAKHOA = K.MAKHOA and K.TENKHOA = N'Sinh học');

--Q71. Cho biết mã số, họ tên, ngày sinh của giáo viên tham gia tất cả các công việc của đề tài “Ứng dụng hóa học xanh”.
--EXCEPT
select GV.MAGV, GV.HOTEN, GV.NGSINH
from GIAOVIEN GV
where not exists(select CV.SOTT
				from CONGVIEC CV, DETAI DT
				where DT.TENDT = N'Ứng dụng hóa học xanh' and DT.MADT = CV.MADT	
				except
				select TGDT.STT
				from THAMGIADT TGDT, DETAI DT2
				where DT2.TENDT = N'Ứng dụng hóa học xanh' and DT2.MADT = TGDT.MADT and GV.MAGV = TGDT.MAGV);

--NOT EXISTS
select GV.MAGV, GV.HOTEN, GV.NGSINH
from GIAOVIEN GV
where not exists( select *  
				from CONGVIEC CV, DETAI DT
				where DT.TENDT = N'Ứng dụng hóa học xanh' and DT.MADT = CV.MADT	
				and not exists(
				select *  
				from THAMGIADT TGDT, DETAI DT2
				where DT2.TENDT = N'Ứng dụng hóa học xanh' and DT2.MADT = TGDT.MADT and GV.MAGV = TGDT.MAGV and CV.SOTT = TGDT.STT));

-- COUNT
select GV.MAGV, GV.HOTEN, GV.NGSINH
from GIAOVIEN GV, DETAI DT, THAMGIADT TG  
where GV.MAGV = TG.MAGV and TG.MADT = DT.MADT and DT.TENDT = N'Ứng dụng hóa học xanh' 
group by GV.MAGV, GV.HOTEN, GV.NGSINH
having count(distinct TG.STT) = (select count(CV.SOTT)
				from CONGVIEC CV, DETAI DT2   
				where DT2.TENDT = N'Ứng dụng hóa học xanh' and DT2.MADT = CV.MADT);


--Q72. Cho biết mã số, họ tên, tên bộ môn và tên người quản lý chuyên môn của giáo viên tham gia tất cả các đề tài thuộc chủ đề “Nghiên cứu phát triển”.
--EXCEPT
select GV.MAGV, GV.HOTEN, BM.TENBM, GVQLBM.HOTEN
from GIAOVIEN GV, GIAOVIEN GVQLBM, BOMON BM
where GV.MABM = BM.MABM and GV.GVQLCM = GVQLBM.MAGV 
				and not exists(select DT.MADT
				from DETAI DT, CHUDE CD
				where CD.TENCD = N'Nghiên cứu phát triển' and CD.MACD = DT.MACD
				except
				select TGDT.MADT
				from THAMGIADT TGDT
				where TGDT.MAGV = GV.MAGV
				);

--NOT EXISTS
select GV.MAGV, GV.HOTEN, BM.TENBM, GVQLCM.HOTEN  
from GIAOVIEN GV, GIAOVIEN GVQLCM, BOMON BM 
where GV.MABM = BM.MABM and GV.GVQLCM = GVQLCM.MAGV 
				and not exists(select *
				from DETAI DT, CHUDE CD
				where CD.TENCD = N'Nghiên cứu phát triển' and CD.MACD = DT.MACD
				and not exists(
				select *
				from THAMGIADT TGDT
				where TGDT.MAGV = GV.MAGV and DT.MADT = TGDT.MADT)
				);

--COUNT
select GV.MAGV, GV.HOTEN, BM.TENBM, GVQLCM.HOTEN  
from GIAOVIEN GV, GIAOVIEN GVQLCM, BOMON BM, THAMGIADT TG, DETAI DT, CHUDE CD    
where GV.MABM = BM.MABM and GV.GVQLCM = GVQLCM.MAGV and TG.MAGV = GV.MAGV and TG.MADT = DT.MADT
and DT.MACD = CD.MACD and CD.TENCD = N'Nghiên cứu phát triển' 
group by  GV.MAGV, GV.HOTEN, BM.TENBM, GVQLCM.HOTEN
having count(distinct DT.MADT) = (select count(DT1.MADT)
				from DETAI DT1, CHUDE CD1
				where CD1.TENCD = N'Nghiên cứu phát triển' and CD1.MACD = DT1.MACD);