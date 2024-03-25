USE leanguage_school
GO

CREATE VIEW Customer_view AS
 SELECT *
 FROM Customer;
 

CREATE VIEW Customer_info_view AS
 SELECT *
 FROM Customer_info;
 
CREATE VIEW Lessons_view AS
 SELECT *
 FROM Lessons;
 
CREATE VIEW Level_view AS
 SELECT *
 FROM Level;
 
CREATE VIEW Teachers_view AS
 SELECT *
 FROM Teachers;



CREATE TRIGGER trigger_on_Customer_info_tbl ON Customer_info AFTER INSERT
AS BEGIN
UPDATE Customer_info SET last_time_active = GETDATE()
FROM INSERTED I,Customer_info tbl
WHERE i.customer_id = tbl.customer_id
END 
Go


INSERT INTO Customer_info(customer_id, email, phone_number)
VALUES (21, 'newemaåêåêå@gmail.com', 997753788);


SELECT *
FROM Customer_info

SELECT *
FROM Customer_info
WHERE phone_number > POWER(27555, 2);


SELECT MAX(age) 
FROM Customer 
WHERE name LIKE 'm%';



SELECT * 
FROM Level 
WHERE begginer > SQRT(8746)





USE leanguage_school

GO
CREATE FUNCTION dbo.one_room_mates()
RETURNS INT
AS BEGIN
DECLARE @Roommates INT;
SELECT @Roommates = (SELECT COUNT(rooms) FROM Lessons WHERE rooms = 1);

RETURN @Roommates;
END



SELECT dbo.One_room_mates() AS Number_of_one_room_mates;



CREATE FUNCTION dbo.English_students()
RETURNS TABLE
AS
RETURN SELECT * FROM Lessons WHERE leanguages LIKE 'E%'
GO




SELECT * FROM dbo.English_students();

