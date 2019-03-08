//
//  ThursdayViewController.swift
//  test
//
//  Created by Shulyugin on 12.12.16.
//  Copyright © 2016 Shulyugin. All rights reserved.
//

import UIKit

class ThursdayViewController: UIViewController, UITableViewDelegate, UITableViewDataSource {
    var items: [String] = ["физика","физика","обж","биология","литература","история","матмод","матмод"]
    var time = ["9:00-9:45","9:55-10:40","10:50-11:35","11:50-12:35","12:45-13:30","13:45-14:30","14:40-15:25","15:35-16:20"]
    
    @IBOutlet weak var TableThursday: UITableView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        TableThursday.delegate = self
        TableThursday.dataSource = self
        TableThursday.tableFooterView = UIView()
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return items.count
    }
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = TableThursday.dequeueReusableCell(withIdentifier: "CellThursday")! as! TableViewCellMonday
        cell.LabelNameThursday.text = items[indexPath.row]
        cell.LabelTimeThursday.text = time[indexPath.row]
        return cell
    }
}
