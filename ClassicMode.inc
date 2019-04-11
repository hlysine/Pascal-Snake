{
  Fix food outside boundary
}

type
  point = record
    x: integer;
    y: integer;
  end;

  procedure classicMode();
  var
    i, j, l, k, d, r1, r2, choice: integer;
    ts: real;
    board: array[1..63, 1..79] of integer;  //1: wall, 2: snake, 3: food
    sBody: array[1..63 * 79] of point;
    score: integer;
    dead: boolean;
    c:  char;
  begin
    txtB(Black);
    ClrScr();
    score := 3;
    ts := TimeStampToMSecS(DateTimeToTimeStamp(now));
    dead := False;
    d  := 1;
    for i := 1 to min(scrH - 1, 79) do
      for j := 1 to min(scrW div 2, 63) do
        board[j, i] := Ord((i = 1) or (j = 1) or (i = min(scrH - 1, 79)) or
          (j = min(scrW div 2, 63)));
    for i := 1 to 1000 do
      board[random(min(scrW div 2, 63) - 2) + 2, random(min(scrH - 1, 79) - 2) + 2] := 3;
    sBody[1].x := min(scrW div 4, 63) - 2;
    sBody[1].y := min(scrH - 1, 79) div 2;
    sBody[2].x := min(scrW div 4, 63) - 1;
    sBody[2].y := min(scrH - 1, 79) div 2;
    sBody[3].x := min(scrW div 4, 63);
    sBody[3].y := min(scrH - 1, 79) div 2;
    gotoxy(1, 1);
    for i := 1 to min(scrH - 1, 79) do
    begin
      l := board[1, i];
      k := 1;
      for j := 2 to min(scrW div 2, 63) do
      begin
        if (board[j, i] <> l) then
        begin
          case l of
            0: txtB(black);
            1: txtB(LightGray);
            2: txtB(LightBlue);
            3: txtB(LightRed);
          end;
          Write('': (j - k) * 2);
          k := j;
          l := board[j, i];
        end;
      end;
      case l of
        0: txtB(black);
        1: txtB(LightGray);
        2: txtB(LightBlue);
        3: txtB(LightRed);
      end;
      Write('': (j - k + 1) * 2);
      {if (scrW mod 2 <> 0) then
        writeln;}
    end;
    gotoxy(1, scrH);
    txtB(Yellow);
    ClrEol();
    printButton(1, scrH, 2, 1, 'UP', 2);
    printButton(4, scrH, 4, 1, 'DOWN', 2);
    printButton(9, scrH, 4, 1, 'LEFT', 2);
    printButton(14, scrH, 5, 1, 'RIGHT', 2);
    repeat
      repeat
        if ((d = 1) and (board[sbody[score].x + 1, sbody[score].y] = 3)) or
          ((d = 2) and (board[sbody[score].x, sbody[score].y + 1] = 3)) or
          ((d = 3) and (board[sbody[score].x - 1, sbody[score].y] = 3)) or
          ((d = 4) and (board[sbody[score].x, sbody[score].y - 1] = 3)) then
        begin
          score := score + 1;
          sbody[score] := sbody[score - 1];
          repeat
            r1 := random(min(scrH - 1, 79) - 2) + 2;
            r2 := random(min(scrW div 2, 63) - 2) + 2;
          until board[r1, r2] = 0;
          board[r1, r2] := 3;
          gotoxy(r1 * 2 - 1, r2);
          txtB(LightRed);
          Write('': 2);
        end
        else if ((d = 1) and (board[sbody[score].x + 1, sbody[score].y] = 2)) or
          ((d = 2) and (board[sbody[score].x, sbody[score].y + 1] = 2)) or
          ((d = 3) and (board[sbody[score].x - 1, sbody[score].y] = 2)) or
          ((d = 4) and (board[sbody[score].x, sbody[score].y - 1] = 2)) then
        begin
          dead := True;
        end
        else if ((d = 1) and (board[sbody[score].x + 1, sbody[score].y] = 1)) or
          ((d = 2) and (board[sbody[score].x, sbody[score].y + 1] = 1)) or
          ((d = 3) and (board[sbody[score].x - 1, sbody[score].y] = 1)) or
          ((d = 4) and (board[sbody[score].x, sbody[score].y - 1] = 1)) then
        begin
          dead := True;
        end
        else
        begin
          board[sbody[1].x, sbody[1].y] := 0;
          gotoxy(sbody[1].x * 2 - 1, sbody[1].y);
          txtB(Black);
          Write('': 2);
          for i := 2 to score do
            sbody[i - 1] := sbody[i];
        end;
        if (d = 1) then
          sbody[score].x := sbody[score].x + 1
        else if (d = 2) then
          sbody[score].y := sbody[score].y + 1
        else if (d = 3) then
          sbody[score].x := sbody[score].x - 1
        else if (d = 4) then
          sbody[score].y := sbody[score].y - 1;
        board[sbody[score].x, sbody[score].y] := 2;
        gotoxy(sbody[score].x * 2 - 1, sbody[score].y);
        txtB(LightBlue);
        Write('': 2);

        txtB(LightCyan);
        txtC(Black);
        gotoxy(scrW div 2 - length(' Score:  ' + IntToStr(score)) div 2, scrH);
        Write(' Score: ', score, ' ');
        repeat
          delay(1);
        until TimeStampToMSecS(DateTimeToTimeStamp(now)) - ts > 50;
        ts := TimeStampToMSecS(DateTimeToTimeStamp(now));
      until keypressed or dead;
      if (not dead) then
      begin
        c := readkey;
        if (c = #0) then
          c := readkey;
        if (c = #77) and (d <> 3) then
          d := 1
        else if (c = #80) and (d <> 4) then
          d := 2
        else if (c = #75) and (d <> 1) then
          d := 3
        else if (c = #72) and (d <> 2) then
          d := 4
        else if (c = #27) then
        begin
          txtB(Cyan);
          txtC(White);
          gotoxy(1, scrH div 2 - 2);
          ClrEol();
          gotoxy(1, scrH div 2 - 1);
          ClrEol();
          gotoxy(1, scrH div 2);
          Write('     Paused');
          ClrEol();
          gotoxy(1, scrH div 2 + 1);
          ClrEol();
          gotoxy(1, scrH div 2 + 2);
          ClrEol();
          choice := 1;
          repeat
            printButton(scrW - 20, scrH div 2 - 1, 8, 0, 'Resume', choice = 1);
            printButton(scrW - 10, scrH div 2 - 1, 8, 0, 'Quit', choice = 2);
            c := readkey;
            if (c = #0) then
              c := readkey;
            if (c = #77) then
            begin
              choice := choice + 1;
              if (choice > 2) then
                choice := 2;
            end
            else if (c = #75) then
            begin
              choice := choice - 1;
              if (choice < 1) then
                choice := 1;
            end
            else if (c = #27) then
            begin
              choice := 1;
              c := #13;
            end;
          until c = #13;
          if (choice = 2) then
            dead := True
          else
          begin
            gotoxy(1, scrH div 2 - 2);
            for i := scrH div 2 - 2 to min(scrH div 2 + 2, 79) do
            begin
              l := board[1, i];
              k := 1;
              for j := 2 to min(scrW div 2, 63) do
              begin
                if (board[j, i] <> l) then
                begin
                  case l of
                    0: txtB(black);
                    1: txtB(LightGray);
                    2: txtB(LightBlue);
                    3: txtB(LightRed);
                  end;
                  Write('': (j - k) * 2);
                  k := j;
                  l := board[j, i];
                end;
              end;
              case l of
                0: txtB(black);
                1: txtB(LightGray);
                2: txtB(LightBlue);
                3: txtB(LightRed);
              end;
              Write('': (j - k + 1) * 2);
              {if (scrW mod 2 <> 0) then
                  writeln;}
            end;
          end;
        end;

      end;
    until dead;
    delay(500);
  end;