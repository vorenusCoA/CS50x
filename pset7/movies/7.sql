SELECT title, rating
  FROM Movies
  JOIN Ratings ON Movies.id = Ratings.movie_id
  WHERE year = 2010
ORDER BY rating DESC, title