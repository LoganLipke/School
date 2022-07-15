# Display two columns: sex, and sex counts. For all employees that work in the company.
SELECT gender AS sex, COUNT(gender) AS sex_counts FROM employees GROUP BY gender;
