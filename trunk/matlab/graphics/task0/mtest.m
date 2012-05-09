function q = mtest(n)
    z = ones(5000) * n;
    q = @summer;
end

function x = summer(i)
    x = i;
end
