SELECT *
	FROM [Customer]

SELECT *
	FROM [Customer_info]

SELECT Customer.customer_id, name, age, email, phone_number
	FROM Customer
	INNER JOIN Customer_info ON Customer.customer_id = Customer_info.customer_id;
	
SELECT Customer.customer_id, name, age, email, phone_number
	FROM Customer
	RIGHT JOIN Customer_info ON Customer.customer_id = Customer_info.customer_id;

SELECT Customer.customer_id, name, age, email, phone_number
	FROM Customer
	LEFT JOIN Customer_info ON Customer.customer_id = Customer_info.customer_id

SELECT Customer.customer_id, name, age, email, phone_number
	FROM Customer
	RIGHT JOIN Customer_info ON Customer.customer_id = Customer_info.customer_id
	WHERE email IS NOT NULL;