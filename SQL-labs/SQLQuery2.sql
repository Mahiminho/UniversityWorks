SELECT *
	FROM Customer


SELECT TOP (200) [customer_id],
		[leanguages],
		[rooms]
	FROM Lessons


SELECT [teacher_name]
	FROM [Teachers]


SELECT [teacher_name]
	FROM [Teachers]
	WHERE teacher_age > 31;


SELECT *
	FROM [Level]
	WHERE middle > 70 OR pro > 70;


SELECT [customer_id],
		[name]
	FROM [Customer]
	WHERE age < 15;

SELECT *
	FROM [Lessons]
	WHERE leanguages LIKE 'English%';


SELECT [customer_id],
		[phone_number]
	FROM [Customer_info]
	WHERE email LIKE 'user%';


SELECT [customer_id],
		[leanguages]
	FROM [Lessons]
	WHERE tests LIKE 'TOEIC%' OR tests LIKE 'IELTS%';


SELECT *
	FROM [Customer_info]
	WHERE email IS NOT NULL;


SELECT COUNT(customer_id), teacher_age
	FROM [Teachers]
	GROUP BY teacher_age;


SELECT COUNT(customer_id), name
	FROM [Customer]
	GROUP BY name;


SELECT COUNT(customer_id), email
	FROM [Customer_info]
	GROUP BY email;


SELECT COUNT(customer_id), teacher_age
	FROM [Teachers]
	GROUP BY teacher_age
	HAVING COUNT(customer_id) > 1;


SELECT COUNT(customer_id), rooms
	FROM [Lessons]
	GROUP BY rooms
	HAVING COUNT(customer_id) > 3;


SELECT COUNT(customer_id), leanguages
	FROM [Lessons]
	GROUP BY leanguages
	HAVING COUNT(customer_id) > 1;


SELECT *
	FROM Lessons
	ORDER BY leanguages;


SELECT *
	FROM Lessons
	ORDER BY rooms;


SELECT [name]
	FROM Customer
	ORDER BY age;






INSERT INTO [Customer]
		([customer_id],
		[name],
		[age])
	VALUES
		(11, 'Artem', 14),
		(12, 'Ioan', 14),
		(13, 'Alves', 14),
		(14, 'Roman', 14),
		(15, 'Inna', 14)
GO

DELETE FROM Customer_info 
	WHERE email IS NOT NULL;


CREATE TABLE Teammates
	(customer_id int,
	teammate_name varchar(20), 
	teammate_age int);DROP TABLE Teammates;