function f = exper(x)
    tmp = ones(10000);
    f = b(x);
end

function f = b(x)
    f = @(y) x + y;
end
