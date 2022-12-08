SELECT * FROM expenses_ticket LIMIT 5;
-- id | ticket_text | pub_date | money | account_id 

SELECT * FROM expenses_bankaccount LIMIT 5;
-- id | account_text | creation_date | money  



CREATE INDEX idx_ticket_text ON expenses_ticket (ticket_text, money);
DROP INDEX idx_ticket_text;
vacuum;


EXPLAIN ANALYZE

SELECT 
    eb.id, 
    eb.account_text, 
    et.ticket_text,
    SUM(et.money) AS total_money_spent,
    -- AVG(et.money) AS average_money_spent,
    COUNT(et.money) AS total_actions
FROM expenses_bankaccount eb
JOIN expenses_ticket      et ON (et.account_id = eb.id)
WHERE LOWER(et.ticket_text) LIKE 'pizza%'
  AND et.money = 10
GROUP BY eb.id, et.ticket_text
ORDER BY total_money_spent DESC;

-- without index
-- Time: 174.656 ms

-- with index
-- Time: 54.545 ms

SELECT 
FROM expenses_bankaccount eb
JOIN expenses_ticket et ON (et.account_id = eb.id)
