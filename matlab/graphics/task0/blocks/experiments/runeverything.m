vis = 1;

run_quickrec
if vis
  %visgraz
  fprintf('\n\n---------------------------------------------------\n\n')
  visp07
  fprintf('\n\n---------------------------------------------------\n\n')
  visp07off
  fprintf('\n\n---------------------------------------------------\n\n')
  visp07s
  fprintf('\n\n---------------------------------------------------\n\n')
  visp07s6
  %visp09
end

return;

run_aibloc
if vis
 vis_aibloc 
end

run_aib
if vis
  vis_aib 
end

