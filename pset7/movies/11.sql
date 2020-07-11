SELECT title
  FROM Movies
  JOIN Ratings ON Movies.id = Ratings.movie_id
  JOIN Stars ON Movies.id = Stars.movie_id
  JOIN People ON Stars.person_id = People.id
  WHERE name = 'Chadwick Boseman'
  ORDER BY rating DESC
  LIMIT 5